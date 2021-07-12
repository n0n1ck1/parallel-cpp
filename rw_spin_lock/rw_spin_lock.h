#pragma once

#include<atomic>
#include<thread>
#include<limits>

class RWSpinLock {
 public:
  RWSpinLock() {
  }

  void LockRead() {
    uint64_t check_parity = counter | 1;
    while (counter.compare_exchange_weak(check_parity, counter + 2)) {
      std::this_thread::yield();
      check_parity = counter | 1;
    }
  }

  void UnlockRead() {
    counter -= 2;
  }

  void LockWrite() {
    uint64_t check_parity = counter | 1;
    while (counter.compare_exchange_weak(check_parity, counter + 1)) {
      std::this_thread::yield();
      check_parity = counter | 1;
    }
    while (counter > 1) {
      std::this_thread::yield();
    }
  }

  void UnlockWrite() {
    counter -= 1;
  }

 private:
  std::atomic<uint64_t> counter = 0;
};
