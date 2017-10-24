//
//  Extended_queue.hpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#ifndef Extended_queue_hpp
#define Extended_queue_hpp

#include "global.hpp"

const int MAX_SIZE = 500;

template <typename Queue_entry>
class Extended_queue {
private:
    int count;
    int front, rear;
    Queue_entry data[MAX_SIZE];
public:
    Extended_queue();
    Error_code append(const Queue_entry& item);
    Error_code serve();
    Error_code retrieve(Queue_entry& item) const;
    bool empty() const;
    int size() const;
};

#include "../src/Extended_queue.cpp"

#endif /* Extended_queue_hpp */
