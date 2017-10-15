#include "dbmanager.h"
#include <folly/Singleton.h>
#include <utility>

namespace cxxdoor {

namespace {
struct DbManagerTag {};
}

static folly::Singleton<DbManager, DbManagerTag> the_instance;
// DbManager::DbManager() {}

DbManager::DbManager(std::string db_name) : _db_name(std::move(db_name)) {
  LOG(INFO) << "Initializing DbManager";
  rocksdb::DB *db;
  rocksdb::Options options;
  options.create_if_missing = true;

  rocksdb::DB::Open(options, _db_name, &db);
  _db.reset(db);
}

std::shared_ptr<DbManager> DbManager::getInstance() {
  return the_instance.try_get();
}
}
