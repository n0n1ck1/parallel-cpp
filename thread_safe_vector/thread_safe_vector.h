#pragma once

#include <vector>
#include<mutex>
#include<shared_mutex>

template <typename T>
class ThreadSafeVector {
 public:
  ThreadSafeVector() {
  }

  T operator[](size_t index) const {
    std::shared_lock lock(read_mutex_);
    return vector_[index];
  }

  size_t Size() const {
    std::unique_lock lock(write_mutex_);
    return vector_.size();
  }

  void PushBack(const T& value) {
    std::unique_lock lock(write_mutex_);
    if (vector_.capacity() == vector_.size()) {
      std::unique_lock lock_read(read_mutex_);
      vector_.push_back(value);
      return;
    }
    vector_.push_back(value);
  }

 private:
  // Your code
  mutable std::shared_mutex read_mutex_;
  mutable std::mutex write_mutex_;
  std::vector<T> vector_;
};
