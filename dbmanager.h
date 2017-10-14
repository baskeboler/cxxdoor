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

  template <class T> void save(const std::string &key, T &entity) {
    using boost::archive::text_oarchive;
    std::stringstream ss;
    text_oarchive ar(ss);
    ar << entity;
    LOG(INFO) << "Serialized entity: " << ss.str();
    rocksdb::Status status = _db->Put(rocksdb::WriteOptions(), key, ss.str());
    if (status.ok()) {
      LOG(INFO) << "Successfully save entity to DB";
    } else {
      LOG(ERROR) << status.ToString();
      throw std::runtime_error(status.ToString());
    }
  }

  template <class T> void save(T &entity) {
    const std::string key =
        dynamic_cast<RocksEntity&>(entity).rocksdb_key().get_value_or(
            dynamic_cast<RocksEntity&>(entity).new_rocksdb_key());
    save(key, entity);
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
