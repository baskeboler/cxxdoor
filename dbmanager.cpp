#include "dbmanager.h"
#include <string>
#include <vector>
#include <map>
#include <rocksdb/db.h>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <folly/Singleton.h>
namespace cxxdoor {

    namespace {
        struct DbManagerTag {
        };
    }

    static folly::Singleton<DbManager, DbManagerTag> the_instance;

    DbManager::DbManager(std::string db_name) : _db_name(db_name) {
        LOG(INFO) << "Initializing DbManager";
        rocksdb::DB *db;
        rocksdb::Options options;
        options.create_if_missing = true;
        std::vector<std::string> cfNames;
        std::vector<rocksdb::ColumnFamilyDescriptor> cfDescr;
        std::vector<rocksdb::ColumnFamilyHandle*> cfHandles;
        auto s = rocksdb::DB::ListColumnFamilies(options, _db_name, &cfNames);
        for (auto& cfName: cfNames) {
            cfDescr.push_back(rocksdb::ColumnFamilyDescriptor(cfName, rocksdb::ColumnFamilyOptions()));
        }
        rocksdb::DB::Open(options, _db_name, cfDescr, &cfHandles, &db);
        if (!s.ok()) {
            LOG(WARNING) << s.ToString();
        }
        for (int i=0; i < cfHandles.size(); i++) {
          _columnFamilies[cfNames[i]] = cfHandles[i];
        }
        LOG(INFO) << "Listing column families";
        for (auto f: cfNames) LOG(INFO) << f;

        // save delete handler for DB
        std::unique_ptr<rocksdb::DB, std::function<void(rocksdb::DB*)>> tmp(db, [&](rocksdb::DB * ptr) {
            LOG(INFO) << "Destroying DB";
            for (auto cf: _columnFamilies) {
                auto h = cf.second;
                auto s = ptr->DestroyColumnFamilyHandle(h);
                if (!s.ok()) {
                    LOG(WARNING) << s.ToString();
                }
            }
          delete ptr;
        });
        _db = std::move(tmp);
    }

    std::shared_ptr<DbManager> DbManager::getInstance() {
        return the_instance.try_get();
    }

    DbManager::~DbManager() {

    }
}
