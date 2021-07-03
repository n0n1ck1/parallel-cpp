#pragma once

#include <ostream>
#include <string_view>
#include <thread>
#include <mutex>
#include <vector>

class HelloWorld {
 public:
  static constexpr std::string_view kHelloPrefix = "Hello, World! From thread ";

  HelloWorld(size_t n_threads)
  {
    n = n_threads;
  }

  void SayHello(std::ostream& os) {
    std::mutex m;
    for (size_t i = 0; i < n; ++i) {
      threads.emplace_back([&]{
        std::unique_lock<std::mutex> lock(m);
        os << kHelloPrefix << std::this_thread::get_id() << '\n';
      });
    }
    for (auto& t : threads) {
      t.join();
    }
  }

 private:
   size_t n;
   std::vector<std::thread> threads;
};
