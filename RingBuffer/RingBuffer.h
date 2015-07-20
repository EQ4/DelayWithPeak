//
//  RingBuffer.h
//  RingBuffer
//
//  Created by Hosack, Matthew on 7/17/15.
//  Copyright (c) 2015 Hosack, Matthew. All rights reserved.
//

#ifndef __RingBuffer__RingBuffer__
#define __RingBuffer__RingBuffer__

#include <atomic>

template <class T>
class RingBuffer
{
private:
    T *p_buf;
    size_t length;
    std::atomic<unsigned int> read;
    std::atomic<unsigned int> write;

public:
    RingBuffer(const unsigned long maxlength) :
        p_buf(new T[maxlength + 1])
        ,length(maxlength + 1)
        ,read(0)
        ,write(0){};
    
    ~RingBuffer() {
        delete [] p_buf;
    }

    int push(const T &input) {
        p_buf[write++] = input;
        if(write.load() >= length)
            write -= (int)length;
        
        if (write.load() == read.load()) {
            read++;
        }

        return 0;
    }
    
    int pop(T &output) {
        output = p_buf[read++];
        if(read.load() >= length)
            read -= (int)length;

        return 0;
    }
    
    /* Helper functions */
    bool isEmpty() {
        return this->size() == 0;
    }
    size_t available() {
        return length - 1 - this->size();
    }
    size_t size() {
        return (read > write) ? (write + (int)length) - read : write - read;
    }
};

#endif /* defined(__RingBuffer__RingBuffer__) */
