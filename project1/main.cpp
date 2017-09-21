//
//  main.cpp
//  TrainChanger
//
//  Created by zhongwq on 2017/9/21.
//  Copyright © 2017年 zhongwq. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<stack<int>> temp_stack;
vector<int> output;
int n, input[20], step = 1;

void printStep(){
    cout << endl;
    cout << "------------------------------------------------" << endl;
    cout << "It's the " << step++ << " step: " << endl;
    cout << "Out Train: ";
    for (auto num: output) {
        cout << num << " ";
    }
    cout << endl;
    for (int i = 0; i < temp_stack.size(); i++) {
        cout << "Stack" << i+1 << ": ";
        if (temp_stack[i].empty()){
            cout << "empty" << endl;
            continue;
        }
        stack<int> temp1, temp2;//temp1 for normal order data, temp2 for flashbacking the number
        temp1 = temp_stack[i];
        while (!temp1.empty()) {
            temp2.push(temp1.top());
            temp1.pop();
        }
        while (!temp2.empty()) {
            cout << temp2.top() << " ";
            temp2.pop();
        }
        cout << endl;
    }
    cout << "------------------------------------------------" << endl;
    cout << endl;
};

bool searchValid(int& output_rear) {
    bool flag = false;
    for (int i = 0; i < temp_stack.size(); i++) {
        if (temp_stack[i].empty()) {
            continue;
        }
        while (!temp_stack[i].empty() && temp_stack[i].top() == output_rear) {
            output.push_back(temp_stack[i].top());
            temp_stack[i].pop();
            ++output_rear;
            printStep();
            flag = true;
        }
    }
    return flag;
}

void distribute() {
    int output_rear = 1;
    for (int i = 0; i < n; i++) {
        if (input[i] == output_rear) {
            output.push_back(input[i]);
            ++output_rear;
            printStep();
            while(searchValid(output_rear)) {
            }
        } else {
            bool flag = false;//record whether found the valid stack
            for (int j = 0; j < temp_stack.size(); j++) {
                if (temp_stack[j].empty()) {
                    temp_stack[j].push(input[i]);
                    flag = true;
                    break;
                }
                if (temp_stack[j].top() < input[i]) {
                    continue;
                }
                temp_stack[j].push(input[i]);
                flag = true;
                break;
            }
            if (!flag) {
                stack<int> new_stack;
                new_stack.push(input[i]);
                temp_stack.push_back(new_stack);
            }
            printStep();
        }
        if (i == n && output_rear != input[n-1]) {
            while(searchValid(output_rear)) {
            }
        }
    }
}

void run(){
    cout << "How many number do you want to input?" << endl;
    cin >> n;
    cout << "Input your number:";
    for (int i = 0; i < n; i++) {
        cin >> input[i];
    }
    distribute();
};

int main() {
    run();
    return 0;
}
