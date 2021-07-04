#pragma once
#include<atomic>
#include<thread>
class TicketLock {
 public:
  TicketLock() {
  }

  void Lock() {
    my_ticket = next.exchange(next + 1);
    while(my_ticket != now) {
      std::this_thread::yield();
    }
  }

  void Unlock() {
    now.fetch_add(1);
  }

 private:
  std::atomic<uint64_t> my_ticket;
  std::atomic<uint64_t> now = 0, next = 0;
};
