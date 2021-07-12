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
    std::shared_lock lock(mutex_);
    return vector_[index];
  }

  size_t Size() const {
    std::shared_lock lock(mutex_);
    return vector_.size();
  }

  void PushBack(const T& value) {
    if (vector_.capacity() == vector_.size()) {
      vector_.push_back(value);
      return;
    }
    std::unique_lock lock(mutex_);
    vector_.push_back(value);
  }

 private:
  // Your code
  mutable std::shared_mutex mutex_;
  std::vector<T> vector_;
};
