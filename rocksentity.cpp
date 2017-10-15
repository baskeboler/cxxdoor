#include "rocksentity.h"

namespace cxxdoor {

std::ostream &operator<<(std::ostream &os, const RocksEntity &c) {
  os << "entity id " << c._id;
  return os;
}

RocksEntity::RocksEntity() = default;

    std::string RocksEntity::entity_class() const {
  return boost::typeindex::type_id_runtime(*this).pretty_name();
}

std::string RocksEntity::generateId() {
  boost::uuids::random_generator gen;
  boost::uuids::uuid random_uuid = gen();
  return boost::uuids::to_string(random_uuid);
}

std::string RocksEntity::getId() const { return _id; }

void RocksEntity::setId(const std::string &id) { _id = id; }

boost::optional<std::string> RocksEntity::rocksdb_key() const {
  if (is_rocksdb_key_valid()) {
    std::stringstream ss;
    ss << entity_class() << "/" << _id;
    return ss.str();
  }
    return boost::none;
}

std::string RocksEntity::new_rocksdb_key() {
    _id = generateId();
    return rocksdb_key().get();
}

bool RocksEntity::is_rocksdb_key_valid() const { return !_id.empty(); }

    bool RocksEntity::operator==(const RocksEntity &rhs) const {
      return _id == rhs._id;
    }

    bool RocksEntity::operator!=(const RocksEntity &rhs) const {
      return !(rhs == *this);
    }
}
