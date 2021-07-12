#pragma once

#include <optional>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
 public:
  ThreadSafeQueue() {
  }

  void Push(const T& value) {
    // Your code
    std::unique_lock lock(mutex_);
    queue_.push(value);
  }

  T Pop() {
    // Your code
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&]{
      return !(queue_.empty());
    });
    auto value = queue_.front();
    queue_.pop();
    return value;
  }

  std::optional<T> TryPop() {
    // Your code
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty()) {
      return std::nullopt;
    }
    auto value = queue_.front();
    queue_.pop();
    return value;
  }


 private:
  // Your code
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cv_;
};
