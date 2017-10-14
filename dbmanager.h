#ifndef DBMANAGER_H
#define DBMANAGER_H
#include "dbconfig.h"
#include "rocksentity.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <glog/logging.h>
#include <istream>
#include <memory>
#include <rocksdb/db.h>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#include <boost/archive/text_oarchive.hpp>

namespace cxxdoor {

class DbManager {
public:
  DbManager(std::string db_name = CXXDOOR_DBNAME);

  template <class T>
  void save(T &entity){
      using boost::archive::text_oarchive;
      // using boost::archive::save;

      std::stringstream ss;
      text_oarchive ar(ss);
      ar << entity;
      std::string key =
          entity.rocksdb_key().get_value_or(entity.new_rocksdb_key());
      //        std::string value;

      //  auto json = entity->get_json();
      //  ss << json;
      //    value = ss.str();
      LOG(INFO) << "Serialized entity: " << ss.str();
      rocksdb::Status status = _db->Put(rocksdb::WriteOptions(), key, ss.str());
      if (status.ok()) {
        LOG(INFO) << "Successfully save entity to DB";
      } else
        throw std::runtime_error(status.ToString());
  }

  template <class T> void load(std::string key, T &entity) {
    LOG(INFO) << "fetching object with key: " << key;
    std::string objstring;
    auto s = _db->Get(rocksdb::ReadOptions(), key, &objstring);
    if (s.ok()) {
      LOG(INFO) << "Successfully recovered value: " << objstring;
      // char * cstr = objstring.c_str();
      // membuf buf(cstr, cstr + objstring.size());
      std::istringstream is;
      is.rdbuf()->str(objstring);
      boost::archive::text_iarchive ar(is);
      ar >> entity;
    } else
      throw std::runtime_error(s.ToString());
  }

  static std::shared_ptr<DbManager> getInstance();

private:
  std::unique_ptr<rocksdb::DB> _db;
  std::string _db_name;
};
}

#endif // DBMANAGER_H
