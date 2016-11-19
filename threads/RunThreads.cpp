#include <string>
#include <iostream>
#include <vector>
#include <thread>

void first() {
  std::cout << "Thread 1" << std::endl;
}

void second() {
  std::cout << "Thread 2" << std::endl;
}

int main() {
  std::thread t1(first);
  std::thread t2(second);

  t1.join();
  t2.join();
  return 0;
}
