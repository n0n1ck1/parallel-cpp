#pragma once
#include<atomic>
#include<thread>

class TicketLock {
 public:
  TicketLock() {
  }

  void Lock() {
    int64_t my_ticket;
    my_ticket = next_.fetch_add(1);
    while (my_ticket != now_) {
      std::this_thread::yield();
    }
  }

  void Unlock() {
    now_.fetch_add(1);
  }

 private:
  std::atomic<uint64_t> now_{0};
  std::atomic<uint64_t> next_{0};
};
