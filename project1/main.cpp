//
//  main.cpp
//  TrainDistributingSystem
//
//  Created by zhongwq on 2017/9/21.
//  Copyright © 2017年 zhongwq, zhouwb, zhouzh. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

vector<stack<int>> temp_stack;
vector<int> output;
int n, input[20], step, now;

void printStep(){
    cout << endl;
    cout << "------------------------------------------------" << endl;
    cout << "It's the " << step++ << " step: " << endl;
    cout << "In Train: ";
    for (int i = now; i < n; i++) {
        cout << input[i] << " ";
    }
    cout << endl;
    cout << "Out Train: ";
    for (auto num: output) {
        cout << num << " ";
    }
    cout << endl;
    for (int i = 0; i < temp_stack.size(); i++) {
        cout << "Stack_" << i+1 << ": ";
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
    now = 0;
    for (int i = 0; i < n; i++) {
        if (input[i] == output_rear) {
            output.push_back(input[i]);
            ++now;
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
            now++;
            printStep();
        }
    }
    if (now == n && output_rear != input[n-1]) {
        while(searchValid(output_rear)) {
        }
    }
    cout << "It used " << temp_stack.size() << " stack(s) and " << step-1 << " step(s) to distribute the trains." << endl;
    system("pause");
}



void run(){
	int status = 0;
	cout << "How many numbers do you want to input?" << endl;
	cin >> n;
	while (cin.fail() || n <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "The numbers can't be a negative number and letters!" << endl;
		cout << "Please input again:";
		cin >> n;
	}
	while (1) {
		if (status == 1)
			cout << "Some of your input is letter!" << endl;
		if (status == 2)
			cout << "Some of your input is overflow!" << endl;
		cout << "Input your numbers(Please enter space between each number):" << endl;
		for (int i = 0; i < n; i++) {
			cin >> input[i];
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				status = 1;
				break;
			} else if (input[i] > n || input[i] <= 0) {
				status = 2;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			if (i == n - 1) {
				status = 0;
			}
		}
		if (status == 0)
			break;
	}
	distribute();
};

void UI() {
	vector<stack<int>> new_stack;
	temp_stack = new_stack;
	vector<int> new_output;
	output = new_output;
	step = 1;
	system("cls");
	cout << "----------------------------------------------------------------------" << endl
		 << "Welcome to our Project One!" << endl
		 << "s - start a new test" << endl
		 << "e - exit" << endl
		 << "----------------------------------------------------------------------" << endl
		 << "Please input your choice: ";
	string command;
	cin >> command;
	if(command == "s"){
		system("cls");
		run();
		system("pause");
		UI();
	} else if(command == "e")
		system("pause");
	else {
		cout << "Please input s or e!" << endl;
		system("pause");
		UI();
	}
}

int main() {
    UI();
    return 0;
}
