#pragma once
#include<mutex>
#include<thread>
#include<chrono>

using namespace std::chrono_literals;

class Deadlock {
 public:
  Deadlock() {
  }

  void ThreadOne() {
    std::unique_lock<std::mutex> first_lock(first_mutex_);
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> second_lock(second_mutex_);
  }

  void ThreadTwo() {
    std::unique_lock<std::mutex> second_lock(second_mutex_);
    std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> first_lock(first_mutex_);
  }

 private:
  std::mutex first_mutex_;
  std::mutex second_mutex_;
};
