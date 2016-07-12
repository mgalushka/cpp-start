#include <fenv.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
#include <thread>
#include <chrono>
#include <mutex>

#include <folly/Conv.h>
#include <folly/dynamic.h>
#include <folly/json.h>

void print(const folly::dynamic& arr) {
  for (const auto& row : arr) {
      std::cout << row << std::endl;
  }
}

int main(int, char**) {
    try{
      auto emptyJson = folly::parseJson("");
    } catch (std::exception& ex) {

      std::cout << ex.what() << std::endl;
    }
    auto mergeFields = folly::parseJson("{}");
    //print(mergeFields);

    mergeFields = folly::parseJson("{\"some_field\": \"value\", \"log_type\": \"SCUBA\"}");
    //print(mergeFields);

    std::cout << "Count(some_field) = " << mergeFields.count("some_field") << std::endl;
    std::cout << "Count(some_field0) = " << mergeFields.count("some_field0") << std::endl;


    std::cout << "is_string_literal = " << std::is_literal_type<std::string>::value << std::endl;
    std::cout << "is_StringPiece_literal = " << std::is_literal_type<folly::StringPiece>::value << std::endl;

    return 0;
}
