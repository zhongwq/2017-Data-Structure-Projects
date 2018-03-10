//
//  Extended_queue.cpp
//  Airport Simulation
//
//  Created by zhongwq on 2017/10/18.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

template <typename Queue_entry>
Extended_queue<Queue_entry>::Extended_queue() {
    count = 0;
    front = 0;
    rear = MAX_SIZE-1;
    memset(data, 0, MAX_SIZE);
}

template <typename Queue_entry>
Error_code Extended_queue<Queue_entry>::append(const Queue_entry& item) {
    if (count >= MAX_SIZE)
        return overflow;
    count++;
    rear = (rear+1)%MAX_SIZE;
    data[rear] = item;
    return success;
}

template <typename Queue_entry>
Error_code Extended_queue<Queue_entry>::serve() {
    if (count <= 0)
        return underflow;
    count--;
    front = (front+1)%MAX_SIZE;
    return success;
}

template <typename Queue_entry>
Error_code Extended_queue<Queue_entry>::retrieve(Queue_entry& item) const{
    if (count <= 0)
        return underflow;
    item = data[front];
    return success;
}

template <typename Queue_entry>
bool Extended_queue<Queue_entry>::empty() const{
    return (count == 0);
}

template <typename Queue_entry>
bool Extended_queue<Queue_entry>::isFull() const{
    return (count == MAX_SIZE);
}

template <typename Queue_entry>
int Extended_queue<Queue_entry>::size() const{
    return count;
}
