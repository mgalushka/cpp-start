#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::promise<int32_t> prom;

void first() {
  std::cout << "Thread 1" << std::endl;
  prom.set_value(700);
}

void second() {
  std::cout << "Thread 2" << std::endl;
  auto fut = prom.get_future();
  std::cout << "Promise value: " << fut.get() << std::endl;
}

int main() {
  using namespace std::chrono_literals;

  std::thread t1(second);
  std::this_thread::sleep_for(300ms);
  std::thread t2(first);

  t1.join();
  t2.join();
  return 0;
}
