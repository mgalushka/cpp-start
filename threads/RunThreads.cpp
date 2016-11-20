#include <string>
#include <iostream>
#include <vector>
#include <thread>

void first(std::vector<std::string>& values) {
  values.reserve(100);
  for (int i = 0; i < 100; ++i) {
    values.emplace_back(std::to_string(i));
  }
  std::cout << "Thread 1" << std::endl;
}

void second() {
  std::cout << "Thread 2" << std::endl;
}

int main() {
  std::vector<std::string> values;
    
  std::thread t1(first, std::ref(values));
  std::thread t2(second);

  t1.join();
  t2.join();
  
  for (auto& value : values) {
    std::cout << value << std::endl;
  }
  
  return 0;
}
