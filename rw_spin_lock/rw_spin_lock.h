#pragma once

#include<atomic>
#include<thread>
#include<limits>

class RWSpinLock {
 public:
  RWSpinLock() {
  }

  void LockRead() {
    uint64_t check_parity = counter_ | 1;
    while (counter_.compare_exchange_weak(check_parity, counter_ + 2)) {
      std::this_thread::yield();
      check_parity = counter_ | 1;
    }
  }

  void UnlockRead() {
    counter_ -= 2;
  }

  void LockWrite() {
    uint64_t check_parity = counter_ | 1;
    while (counter_.compare_exchange_weak(check_parity, counter_ + 1)) {
      std::this_thread::yield();
      check_parity = counter_ | 1;
    }
    while (counter_ > 1) {
      std::this_thread::yield();
    }
  }

  void UnlockWrite() {
    counter_ -= 1;
  }

 private:
  std::atomic<uint64_t> counter_ = 0;
};
