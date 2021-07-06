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
    left_fork_.lock();
    std::this_thread::sleep_for(10ms);
    right_fork_.lock();
    left_fork_.unlock();
    right_fork_.unlock();
  }

  void ThreadTwo() {
    right_fork_.lock();
    std::this_thread::sleep_for(10ms);
    left_fork_.lock();
    right_fork_.unlock();
    left_fork_.unlock();
  }

 private:
  std::mutex left_fork_;
  std::mutex right_fork_;
};
