#pragma once
#include<atomic>
#include<thread>
#include<limits>

class RWSpinLock {
 public:
  RWSpinLock() {
  }

  void LockRead() {
    // 18 446 744 073 709 551 615 = std::numertic_limits<uint64_t> - 1
    // this way i check if counter is even or not
    while (std::atomic_fetch_or(&counter, 1) == counter) {
      std::this_thread::yield();
    }
    counter += 2;
  }

  void UnlockRead() {
    counter -= 2;
  }

  void LockWrite() {
    while (std::atomic_fetch_or(&counter, 1) == counter) {
      std::this_thread::yield();
    }
    counter += 1;
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
