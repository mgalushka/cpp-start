#include <folly/detail/CacheLocality.h>
#include <iostream>

#include "gtest/gtest.h"
#include "glog/logging.h"

namespace cacheline {
    using namespace folly::detail;    

    CacheLocality cacheLocality;
}




int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);

  std::cout << "Num CPUs: " << cacheline::cacheLocality.numCpus << std::endl;

  int cacheNumber = 0;
  for (size_t cache : cacheline::cacheLocality.numCachesByLevel) {
      std::cout << "Num caches (level=" << cacheNumber << "): " <<  cache << std::endl;
      cacheNumber++;
  }

  return 0;
}