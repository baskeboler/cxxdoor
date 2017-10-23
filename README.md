# cxxdoor

A toy, proof of concept application demonstrating the use of Facebook c++ libraries such as proxygen, folly and RocksDB for the development of HTTP services. **Please note that this is a work-in-progress and its only purpose is to demo and integrate different libraries, do not expect production grade software.**

## dependencies

* proxygen
* folly 
* boost c++ libraries
* crypto++
* rocksdb
* wangle
* pthread
* gflags
* glog
* SSL
* gtest (for unit testing)


## notes

* CMakeLists.txt
  - cmake file.

### db access

Data access is implemented using RocksDB which is a persistent key/value store that I've used to store individual entities and also entire STL containers such as std::vector and std::map with the help of boost::serialization

#### `boost::serialization`

``` c++
template <class Archive>
 void serialize(Archive &ar, const unsigned int version) {
   ar & boost::serialization::base_object<RocksEntity>(*this);
   ar & nombre &email &password;
}
```

* dbconfig.h
* dbmanager.h


### entities

* booking.h
* rocksentity.h
* usuario.h


### controllers

* BookingController.h
* usuariocontroller.h

#### Use of `folly::Synchronized` and `folly::Singleton`


### Request Handlers

* HandlerFactory.h
* UsuarioHandler.h

### Filters

### Processors
* AddUserProcessor.h
* AuthenticationProcessor.h
* CommandProcessor.h


### unit tests

* main_test.cpp
* bookingstest.cpp
* usuariotest.cpp

