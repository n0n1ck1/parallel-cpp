#pragma once
#include<atomic>
#include<thread>
class SpinLock {
 public:
  SpinLock() {
  }
  void Lock() {
    while(flag.exchange(true)) {
      std::this_thread::yield();
    }
  }

  void Unlock() {
    flag = false;
  }

private:
  std::atomic<bool> flag{false};
};
