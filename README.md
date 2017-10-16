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


``` c++
template <class Archive>
 void serialize(Archive &ar, const unsigned int version) {
   ar & boost::serialization::base_object<RocksEntity>(*this);
   ar & nombre &email &password;
}
```



### entities



### controllers
* BookingController.h

#### Use of `folly::Synchronized` and `folly::Singleton`


### Request Handlers

### Filters

### Processors


### unit tests


* AddUserProcessor.h
* AuthenticationProcessor.h
* CommandProcessor.h
* HandlerFactory.h
* UsuarioHandler.h
* booking.h
* bookingstest.cpp
* dbconfig.h
* dbmanager.h
* main.cpp
* main_test.cpp
* rocksentity.h
* usuario.h
* usuariocontroller.h
* usuariotest.cpp
