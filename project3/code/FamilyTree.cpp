//
//  FamilyTree.cpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017Äê zhongwq. All rights reserved.
//


#include "FamilyTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;
typedef personNode* nodeptr;

int personNode::indexNum = 0;

void push(vector<personNode*> &my,vector<personNode*> add){
    for(int i = 0;i < add.size();i++)
        my.push_back(add[i]);
}

personNode* searchPerson(personNode* root,personNode* parent){
    if(root->right == parent || root->left == parent)
        return root;
    personNode* re = NULL;
    personNode* temp = root;
    if(temp->right != NULL)
        re = searchPerson(temp->right,parent);
    if(re != NULL)
        return re;
    if(temp->left != NULL)
        re = searchPerson(temp->left,parent);
    return re;
}

vector<personNode*> m_queryPerson(personNode* root,function<bool(const personNode*)>filter){
    vector<personNode*> re;
    if(root != NULL){
        if(filter(root))
            re.push_back(root);
        push(re,m_queryPerson(root->right,filter));
        push(re,m_queryPerson(root->left,filter));
    }
    return re;
}

vector<personNode*> m_updatePerson(personNode* root,function<bool(const personNode*)> filter,function<bool(const personNode*)> updater){
    vector<personNode*> re;
    if(root != NULL){
        if(root->left != NULL){
            if(filter(root->left)){
                updater(root->left);
                re.push_back(root->left);
            }
            push(re,m_updatePerson(root->left,filter,updater));
        }
        if(root->right != NULL){
            if(filter(root->right)){
                updater(root->right);
                re.push_back(root->right);
            }
            push(re,m_updatePerson(root->right,filter,updater));
        } 
    }
    return re;
} 

void printSpace(int num){
    for(int i = 0; i < num; i++)
        cout << " ";
}

void myPrint(personNode* root, int num,int position){
    if(root != NULL) {
        if (!(root->index == -1 && root->left == NULL)) {
            printSpace(num);
            if(position == 1)
                cout << "|___";
            else if(position == 2)
                cout << "||__"; 
            cout << root->name << (((root->status) && (root->index != -1))?"(ËÀ)":"") << endl;
        }
        if(position == 1 || position == 0){
            myPrint(root->left,num+4,2);
            myPrint(root->right,num,1);
        }
        else{
            myPrint(root->right,num,1);
            myPrint(root->left,num,2);
        }
    }
}

void deleteTree(nodeptr &root){
	if(root != NULL){
		deleteTree(root->right);
		deleteTree(root->left);
		delete root;
		root = NULL;
	}
}


void m_deleteMember(personNode* root,personNode* person){
	if(root != NULL){
		if(root->left != NULL){
			if(root->left == person){
				deleteTree(root->left->right);
				personNode* temp = root->left;
				root->left = temp->left;
				delete temp;
				return;
			}
			m_deleteMember(root->left,person);
		}
		if(root->right != NULL){
			if(root->right == person){
				deleteTree(root->right->left);
				personNode* temp = root->right;
				if(temp->right->index == -1){
					root->right = temp->right->right;
					delete temp->right;
				}
				else
					root->right = temp->right;
				delete temp;
				return;
			}
			m_deleteMember(root->right,person);
		}
	}
}


bool m_queryParent(personNode* root,personNode* person,vector<personNode*>& re){
	bool is = 0;
	if(root != NULL){
		if(root != person){
			is += m_queryParent(root->left,person,re) + m_queryParent(root->right,person,re);
			if(is)
				re.push_back(root);
		}
		else
			return 1;
	}
	return is;
}

string toString(personNode* person){
	if(person == NULL)
		return "-2";
	stringstream str;
	str << person->index << " " << person->age << " " 
		<< person->name << " " << person->sex << " " 
		<< person->foreign << " " << person->status << " "
		<< person->divorce;
	return str.str(); 
}

FamilyTree::~FamilyTree(){
    deleteTree(root);
}

void FamilyTree::insertAncestor(personNode* person){
    root = person;
}

void FamilyTree::insertChild(personNode* person,personNode* parent){
    if(root == parent){
        if(root->left == NULL)
            root->left = person;
        else{
            personNode* temp = root;
            while((temp->left)->left != NULL)
                temp = temp->left;
            temp->left->left = person;
        }
        return;
    }
    personNode* front = searchPerson(root,parent);
    if(front == NULL)
        return;
    else if(front->right == parent){
        if(front->right->left == NULL)
            (front->right)->left = person;
        else{
            personNode* temp = front->right;
            while((temp->left)->left != NULL)
                temp = temp->left;
            temp->left->left = person;
        }
    }
    else
        if(front->left->left == NULL)
            (front->right)->left = person;
        else{
            personNode* temp = front->left;
            while((temp->left)->left != NULL)
                temp = temp->left;
            temp->left->left = person;
        }
}

void FamilyTree::insertPartner(personNode* person,personNode* partner){
    if(root == partner){
        if(root->right == NULL)
            root->right = person;
        else{
            personNode* temp = root;
            while((temp->right)->right != NULL)
                temp = temp->right;
            temp->right->right = person;
        }
        return;
    }
    personNode* front = searchPerson(root,partner);
    if(front == NULL)
        return;
    else if(front->right == partner)
        if(front->right->right == NULL)
            (front->right)->right = person;
        else{
            personNode* temp = front->right;
            while((temp->right)->right != NULL){
                temp->right->divorce = 1;
                temp = temp->right;
            }
            temp->right->right = person;
        }
    else
        if(front->left->right == NULL)
            (front->left)->right = person;
        else{
            personNode* temp = front->left;
            while((temp->right)->right != NULL){
                temp->right->divorce = 1;
                temp = temp->right;
            }
            temp->right->right = person;
        }
}

void FamilyTree::deleteMember(personNode* person){
    if(root == person){
        deleteTree(root);
		return;
    }
    m_deleteMember(root,person);
}


vector<personNode*> FamilyTree::queryPerson(function<bool(const personNode*)> filter){
    return m_queryPerson(root,filter);
}

vector<personNode*> FamilyTree::updatePerson(function<bool(const personNode*)> filter,function<bool(const personNode*)> updater){
    vector<personNode*> re;
    if(filter(root)){
        updater(root);
        re.push_back(root);
    }
    push(re,m_updatePerson(root,filter,updater));
    return re;
}

int FamilyTree::count(function<bool(const personNode*)> filter){
    vector<personNode*> re= queryPerson(filter);
    return re.size();
}

vector<personNode*> FamilyTree::queryParent(personNode* person){
	vector<personNode*> branch;
	m_queryParent(root,person,branch);
	vector<personNode*> re;
	int key = 0;
	for(int i = 0;i < branch.size();i++){
		if(key == 0 && branch[i]->foreign == 1){
			re.push_back(branch[i]);
			key = 1;
		}
		if(key == 1 && branch[i]->foreign == 0){
			re.push_back(branch[i]);
			break;
		}
	}
	return re;
}


void FamilyTree::printAllPerson(){
    myPrint(root,0,0);
}

bool FamilyTree::empty(){
    return root == NULL;
}

vector<personNode*> FamilyTree::queryPersonFromVector(vector<personNode*> data,function<bool(const personNode*)> filter){
    vector<personNode*> re;
    for(int i = 0;i < data.size();i++){
        if(filter(data[i]))
            re.push_back(data[i]);
    }
    return re;
}

bool FamilyTree::read(string filename) {
	int index, age, sexInt;
	string name;
	bool foreign, status, divorce;
	ifstream file(filename);
	if (!file)
		return false;
	queue<personNode*> que;
	file >> index;
	if(index == -2) {
		root = NULL;
		return true;
	}
	file >> age >> name >> sexInt >> foreign >> status >> divorce;
	root = new personNode(age, name, Sex(sexInt), foreign, status, divorce);
	que.push(root);
	while (!que.empty()) {
		personNode* tmp = que.front();
		que.pop();
		file >> index;
		if (index != -2) {
			file >> age >> name >> sexInt >> foreign >> status >> divorce;
			if (index != -1)
				tmp->left = new personNode(age, name, Sex(sexInt), foreign, status, divorce);
			else
				tmp->left = new personNode;
			que.push(tmp->left);
		}
		file >> index;
		if(index != -2) {
			file >> age >> name >> sexInt >> foreign >> status >> divorce;
			if (index != -1)
				tmp->right = new personNode(age, name, Sex(sexInt), foreign, status, divorce);
			else
				tmp->right = new personNode;
			que.push(tmp->right);
		}
	}
	file.close();
	return true;
}

bool FamilyTree::save(string filename){
	ofstream of(filename);
	if(!of)
		return false;
	queue<personNode*> que;
	que.push(root);
	while(!que.empty()){
		auto temp = que.front();
		of << toString(temp) << endl;
		que.pop();
		if(temp == NULL)
			continue;
		que.push(temp->left);
		que.push(temp->right);
	}
	of.close();
    return true;
}
