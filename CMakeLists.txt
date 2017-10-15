cmake_minimum_required(VERSION 3.0)
project(cxxdoor CXX)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
include_directories(SYSTEM /usr/local/include /usr/include)
link_directories(SYSTEM /usr/local/lib /usr/lib)

find_library(ROCKSDB rocksdb)

set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.60 COMPONENTS date_time filesystem system atomic thread serialization)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

FIND_LIBRARy(FOLLY folly)
FIND_LIBRARY(WANGLE wangle)
FIND_LIBRARY(PTHREAD pthread)
find_library(GLOG glog)
find_library(Z z)
find_library(GFLAGS gflags)
find_library(SSL ssl)
find_library(CRYPTO crypto)
find_library(PROXYGENLIB proxygenlib)
find_library(PROXYGENHTTPSERVER proxygenhttpserver)
find_library(DCONV double-conversion)
find_library(GTEST gtest)
find_library(GTEST_MAIN gtest_main)
find_library(CRYPTO++ crypto++)

set(SRC
    usuario.cpp
    rocksentity.cpp
    dbmanager.cpp
    booking.cpp
    usuariocontroller.cpp)
set(TEST_SRC ${SRC}
    usuariotest.cpp)

set(MAIN main.cpp)
add_library(LIBCXXDOOR SHARED ${SRC})
add_library(LIBCXXDOOR_TEST SHARED ${TEST_SRC})

set(LIBS
    ${Z}
    ${CRYPTO}
    ${CRYPTO++}
    ${SSL}
    ${WANGLE}
    ${PTHREAD}
    ${GLOG}
    ${GFLAGS}
    ${DCONV}
    ${FOLLY}
    ${PROXYGENLIB}
    ${PROXYGENHTTPSERVER}
    ${ROCKSDB}
    ${Boost_LIBRARIES}
    ${LIBCXXDOOR})

set(LIBS_TEST
    ${GTEST}
    ${GTEST_MAIN}
    ${LIBS})


add_executable(${PROJECT_NAME} ${MAIN})
target_link_libraries(${PROJECT_NAME} ${LIBS})


add_executable(main_test main_test.cpp ${TEST_SRC})
target_link_libraries(main_test ${LIBS_TEST})

enable_testing()
add_test(NAME main_test
    COMMAND main_test)
