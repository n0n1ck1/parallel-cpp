#pragma once

#include <mutex>


class Fork {
 public:
  Fork(size_t id) : id_(id) {
  }

  size_t Id() const {
    return id_;
  }

  void Get() {
    mutex_.lock();
  }

  bool TryGet() {
    return mutex_.try_lock();
  }

  void Put() {
    mutex_.unlock();
  }

 private:
  size_t id_;
  std::mutex mutex_;
};

class Philosopher {
 public:
  Philosopher(size_t id, Fork* left_fork, Fork* right_fork) {
    ID = id;
    l = left_fork;
    r = right_fork;
  }

  size_t Id() const {
    return ID;
  }

  void Eat() {
    if (l->Id() < r->Id()) {
      l->Get();
      r->Get();
    } else {
      r->Get();
      l->Get();
    }
  }

  void Think() {
    l->Put();
    r->Put();
  }

private:
  size_t ID;
  Fork* l;
  Fork* r;
};
