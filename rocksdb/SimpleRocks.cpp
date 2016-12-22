#include <cstdio>
#include <iostream>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

using namespace rocksdb;

std::string kDBPath = "/tmp/simple_rocks";

int main() {
  DB* db;
  Options options;

  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();

  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  // write key-value
  s = db->Put(WriteOptions(), "key1", "key1-value");
  assert(s.ok());
  std::string value;

  // read value
  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.ok());
  std::cout << "Value[key1] = " << value << std::endl;

  // atomically apply a set of updates
  {
    WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(WriteOptions(), &batch);
  }

  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.IsNotFound());

  db->Get(ReadOptions(), "key2", &value);
  std::cout << "Value[key2] = " << value << std::endl;

  delete db;

  return 0;
}
