#pragma once
#include <array>
#include <stdexcept>

template<typename T, size_t SIZE>
class RingBuffer {
public:
    RingBuffer() : head_(0), tail_(0), count_(0) {}

    bool push(const T& item) {
        if (count_ >= SIZE) return false;
        buf_[head_] = item;
        head_ = (head_ + 1) % SIZE;
        count_++;
        return true;
    }

    bool pop(T& item) {
        if (count_ == 0) return false;
        item = buf_[tail_];
        tail_ = (tail_ + 1) % SIZE;
        count_--;
        return true;
    }

    bool isEmpty() const { return count_ == 0; }
    bool isFull()  const { return count_ >= SIZE; }
    size_t size()  const { return count_; }
    void clear() { head_ = tail_ = count_ = 0; }

private:
    std::array<T, SIZE> buf_;
    size_t head_, tail_, count_;
};
