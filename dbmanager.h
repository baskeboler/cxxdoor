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
#include <algorithm>
#include <boost/archive/text_oarchive.hpp>
#include <map>

namespace cxxdoor {

    class DbManager {
    public:
        DbManager(std::string db_name = CXXDOOR_DBNAME);

        virtual ~DbManager();

        void validate_column_family(const std::string &cf) {
            auto found = _columnFamilies.find(cf);
            if (found == _columnFamilies.end()) {
                LOG(WARNING) << "Column family " << cf << " does not exist, creating";
                std::shared_ptr<rocksdb::ColumnFamilyHandle> h;
                rocksdb::ColumnFamilyHandle *hh;
                auto s = _db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), cf, &hh);
                if (!s.ok()) {
                    LOG(ERROR) << s.ToString();
                }
                h.reset(hh);
                _columnFamilies[cf] = h;
            }
        }

        template<class T>
        void save(const std::string &key, T &entity, bool useColumnFamily = true) {
            using boost::archive::text_oarchive;
            std::stringstream ss;
            text_oarchive ar(ss);
            ar << entity;
            LOG(INFO) << "Serialized entity: " << ss.str();
            rocksdb::Status status;
            if (useColumnFamily) {
                std::string cfName = boost::typeindex::type_id_runtime(entity).pretty_name();
                validate_column_family(cfName);

                status = _db->Put(rocksdb::WriteOptions(), _columnFamilies[cfName].get(), key, ss.str());
            } else {
                status = _db->Put(rocksdb::WriteOptions(), key, ss.str());

            }
            if (status.ok()) {
                LOG(INFO) << "Successfully save entity to DB";
            } else {
                LOG(ERROR) << status.ToString();
                throw std::runtime_error(status.ToString());
            }
        }

        template<class T>
        void save(T &entity) {
            const std::string key =
                    dynamic_cast<RocksEntity &>(entity).rocksdb_key().get_value_or(
                            dynamic_cast<RocksEntity &>(entity).new_rocksdb_key());
            save(key, entity);
        }

        template<class T>
        bool load(std::string key, T &entity, bool useColumnFamily = true) {
            LOG(INFO) << "fetching object with key: " << key;
            std::string objstring;
            rocksdb::Status s;
            if (useColumnFamily) {
                std::string cfName = boost::typeindex::type_id_runtime(entity).pretty_name();
                validate_column_family(cfName);

                s = _db->Get(rocksdb::ReadOptions(), _columnFamilies[cfName].get(), key, &objstring);
            } else {
                s = _db->Get(rocksdb::ReadOptions(), key, &objstring);
            }
            if (s.ok()) {
                LOG(INFO) << "Successfully recovered value: " << objstring;
                // char * cstr = objstring.c_str();
                // membuf buf(cstr, cstr + objstring.size());
                std::istringstream is;
                is.rdbuf()->str(objstring);
                boost::archive::text_iarchive ar(is);
                ar >> entity;
                return true;
            }
            LOG(WARNING) << s.ToString();
            return false;
        }

        static std::shared_ptr<DbManager> getInstance();

    private:
        std::shared_ptr<rocksdb::DB> _db;
        std::string _db_name;
        std::map<std::string, std::shared_ptr<rocksdb::ColumnFamilyHandle>> _columnFamilies;
    };
}

#endif // DBMANAGER_H
