#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

/// want to pass task from 1 tread to another
std::promise<int32_t> prom;


void second(std::packaged_task<int32_t(int32_t)>& task, int32_t x) {
  std::cout << "Thread 2" << std::endl;
  task(x);
}

int32_t square(int32_t a) {
  return a * a;
}


int main() {
  using namespace std::chrono_literals;
  std::packaged_task<int32_t(int32_t)> task(&square);

  std::future<int32_t> fut = task.get_future();
  std::thread t1(second, std::ref(task), 100);
  std::this_thread::sleep_for(300ms);

  std::cout << "Square result: " << fut.get() << std::endl;

  t1.join();
  return 0;
}
