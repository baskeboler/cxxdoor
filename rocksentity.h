#ifndef ROCKSENTITY_H
#define ROCKSENTITY_H

#include <boost/exception/exception.hpp>
#include <boost/optional.hpp>
#include <boost/type_index.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <folly/dynamic.h>
#include <sstream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/assume_abstract.hpp>
namespace cxxdoor {

class RocksEntity {
  friend boost::serialization::access;
  friend std::ostream &operator<<(std::ostream &os, const RocksEntity &c);

 public:
  RocksEntity();

  template<class Archive>
  void serialize(Archive &a, const unsigned int version) {
    a & _id;
  }

  virtual ~RocksEntity() = default;
  static std::string generateId();

  std::string getId() const;
  void setId(const std::string &id);

  boost::optional<std::string> rocksdb_key() const;
  std::string new_rocksdb_key();

  virtual folly::dynamic get_json() const = 0;

  bool operator==(const RocksEntity &rhs) const;

  bool operator!=(const RocksEntity &rhs) const;

 private:
  std::string _id;
  std::string entity_class() const;

 protected:
  bool is_rocksdb_key_valid() const;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(RocksEntity);
}

#endif // ROCKSENTITY_H
