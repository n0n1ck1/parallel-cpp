#pragma once

#include<atomic>
#include<thread>
#include<limits>

class RWSpinLock {
 public:
  RWSpinLock() {
  }

  void LockRead() {
    while (true) {
      auto loaded_counter = counter_.load();
      if (loaded_counter & 1) {
        std::this_thread::yield();
        continue;
      }
      if (counter_.compare_exchange_weak(loaded_counter, loaded_counter + 2)) {
        return;
      }
    }
  }

  void UnlockRead() {
    counter_.fetch_sub(2);
  }

  void LockWrite() {
    while (true) {
      auto loaded_counter = counter_.load();
      if (loaded_counter & 1) {
        std::this_thread::yield();
        continue;
      }
      if (counter_.compare_exchange_weak(loaded_counter, loaded_counter + 1)) {
        break;
      }
    }
    while (counter_ > 1) {
      std::this_thread::yield();
    }
  }

  void UnlockWrite() {
    counter_.fetch_sub(1);
  }

 private:
  std::atomic<uint64_t> counter_ = 0;
};
