#pragma once

#include <ostream>
#include <string_view>
#include <thread>
#include <mutex>
#include <vector>

class HelloWorld {
 public:
  static constexpr std::string_view kHelloPrefix = "Hello, World! From thread ";

  HelloWorld(size_t n_threads) : n_hellos_(n_threads){
  }

  void SayHello(std::ostream& os) {
    std::mutex mutex;
    std::vector<std::thread> threads_;
    for (size_t i = 0; i < n_hellos_; ++i) {
      threads_.emplace_back([&]{
        std::unique_lock<std::mutex> lock(mutex);
        os << kHelloPrefix << std::this_thread::get_id() << '\n';
      });
    }
    for (auto& t : threads_) {
      t.join();
    }
  }

 private:
   const size_t n_hellos_;
};
