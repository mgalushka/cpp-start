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
#include <thread>
#include <type_traits>

#include <folly/Conv.h>
#include <folly/dynamic.h>
#include <folly/json.h>

void print(const folly::dynamic& arr) {
  for (const auto& row : arr) {
      std::cout << row << std::endl;
  }
}

const std::string kCountPlaceholder  = "##LINES_COUNT##";

std::string getLineWithCount(std::string originalLine, int32_t counter) {
  // will be replacing including quotes
  int32_t begin = originalLine.find(kCountPlaceholder) - 1;
  if (begin < 0) {
    return originalLine;
  }

  return originalLine.replace(begin,
                              kCountPlaceholder.length() + 2,
                              folly::to<std::string>(counter));
}

bool stringFormatGMTimestamp(time_t t, const char* format, std::string* str) {
  struct tm timeinfo;
  gmtime_r(&t, &timeinfo);

  const int BUFSIZE = 256; // should be plenty for any timestamps
  char buf[BUFSIZE];
  if (!strftime(buf, BUFSIZE, format, &timeinfo)) {
    return false;
  }

  if (str) {
    *str = buf;
  }
  return true;
}

bool stringFormatTimestamp(time_t t, const char* format, std::string* str) {
  struct tm timeinfo;
  localtime_r(&t, &timeinfo);

  const int BUFSIZE = 256; // should be plenty for any timestamps
  char buf[BUFSIZE];
  if (!strftime(buf, BUFSIZE, format, &timeinfo)) {
    return false;
  }

  if (str) {
    *str = buf;
  }
  return true;
}

int main(int, char**) {
  //using namespace std::chrono_literals;

  std::string a("aaaaaI\"##LINES_COUNT##\"Iaaaaaaaaaaaaa");
  std::cout << a.find_first_of(kCountPlaceholder) << std::endl;

  std::cout << "getLineWithCount = "
            << getLineWithCount(a, 1) << std::endl;

  folly::dynamic json = folly::dynamic({"test", 1});
  std::string astr = folly::to<std::string>(folly::toJson(json));

  std::cout << astr << std::endl;
  std::cout << astr.size() << std::endl;
  std::cout << sizeof(json) << std::endl;

  folly::dynamic json2 = folly::dynamic({"testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest", 1000});
  std::string astr2 = folly::to<std::string>(folly::toJson(json2));

  std::cout << astr2 << std::endl;
  std::cout << astr2.size() << std::endl;
  std::cout << sizeof(json2) << std::endl;
  std::cout << json2.size() << std::endl;

  folly::dynamic logObj = folly::dynamic::object("query", "why? some fancy phone 123 lalal");
  std::string query = folly::to<std::string>(logObj.getDefault("query", "").asString());
  if (query != "") {
    std::size_t pattern1 = query.find("some fancy phone 123");
    std::size_t pattern2 = query.find("some fancy phone 456");
    if (pattern1 != std::string::npos || pattern2 != std::string::npos) {
      std::cout << "FOUND!" << std::endl;
    }
  }

  folly::dynamic cool = folly::dynamic({"value", "`cool`€€\\\\n"});
  std::cout << folly::toJson(cool) << std::endl;

  folly::json::serialization_opts opts;
  opts.encode_non_ascii = true;
  opts.skip_invalid_utf8 = true;
  std::cout << folly::json::serialize(cool, opts) << std::endl;

  std::string suffix = "Primary";
  auto r = folly::stringPrintf("XXXYYYZZZ%sProcessor", suffix.c_str()).c_str();
  std::cout << r << std::endl;

  int32_t logTime = 1470095999;
  std::string day;
  stringFormatTimestamp(logTime, "day-%F-%H", &day);
  std::cout << day << std::endl;

  stringFormatGMTimestamp(logTime, "day-%F-%H", &day);
  std::cout << day << std::endl;

  auto start = std::chrono::steady_clock::now();
  //std::this_thread::sleep_for(1s);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << diff.count() << std::endl;

  auto now = std::chrono::system_clock::now();
  std::cout << std::chrono::system_clock::to_time_t(now) << std::endl;


  folly::dynamic names_json = folly::dynamic::object("names", {"a", "b", "c"});
  std::cout << folly::toJson(names_json["names"]) << std::endl;

  std::cout << std::is_move_constructible<folly::dynamic>::value << std::endl;
  std::cout << std::is_move_assignable<folly::dynamic>::value << std::endl;

 return 0;
}
