#include "usuario.h"
#include <gtest/gtest.h>
#include <glog/logging.h>
#include "dbmanager.h"
TEST(Usuario, crear_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
}

TEST(Usuario, guardar_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
    cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(u);
}
TEST(Usuario, cargar_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setPassword("thisisapassword");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
    std::string key = u.rocksdb_key().get();
    cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(u);

    cxxdoor::Usuario u2;
    cxxdoor::DbManager::getInstance()->load<cxxdoor::Usuario>(key, u2);
    LOG(INFO) << u2;
}
