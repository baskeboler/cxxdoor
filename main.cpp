#include <iostream>
#include <rocksdb/db.h>

using rocksdb::Slice;

int main(int argc, char *argv[argc]) {
  rocksdb::DB *db;
  rocksdb::Options options;
  options.create_if_missing = true;
  rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());
  std::cout << "hola!"
            << "\n";

  std::string val;

  status = db->Get(rocksdb::ReadOptions(), Slice("key1"), &val);
  if (!status.ok())
    std::cerr << status.ToString() << std::endl;
  return 0;
}
