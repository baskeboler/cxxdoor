#include "usuario.h"
#include "booking.h"
#include "dbmanager.h"
#include "usuariocontroller.h"
#include <glog/logging.h>
#include <gtest/gtest.h>

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
  const std::string &key = u.rocksdb_key().get();
  cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(u);

  cxxdoor::Usuario u2;
  cxxdoor::DbManager::getInstance()->load<cxxdoor::Usuario>(key, u2);
  LOG(INFO) << u2;
}



TEST(UsuarioController, getinstance) {
  auto c = cxxdoor::UsuarioController::getInstance();
}

TEST(UsuarioController, md5) {
  auto c = cxxdoor::UsuarioController::getInstance();

  LOG(INFO) << "md5(hola)" << c->md5("hola");
  LOG(INFO) << "md5(chau)" << c->md5("chau");
  c->crearUsuario("user1", "pass1");
  c->crearUsuario("user2", "pass2");
  GTEST_ASSERT_EQ(c->authenticate("user1", "pass1").is_initialized(), true);
  GTEST_ASSERT_EQ(c->authenticate("user1", "pass11").is_initialized(), false);
}
