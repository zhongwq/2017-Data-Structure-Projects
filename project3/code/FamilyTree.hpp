//
//  FamilyTree.hpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017年 zhongwq. All rights reserved.
//

#ifndef FamilyTree_hpp
#define FamilyTree_hpp

#include <string>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

enum Sex { Male, Female /*, Bisexual*/ };

struct personNode {
    static int indexNum;//静态变量需要初始化
    int index;
    int age;
    string name;
    Sex sex;
    bool foreign;
    //vector<string> extraInfo;
    bool status;//是否死亡
    bool divorce;
    personNode* left;//左边对于该节点为兄弟姐妹关系
    personNode* right;//右边对于该节点为配偶们..即使离婚后也会记录在册：）
    personNode(int age, string name, Sex sex, bool foreign, bool status, bool divorce, personNode* left = NULL, personNode* right = NULL): index(indexNum++), age(age), name(name), sex(sex), foreign(foreign), status(status), divorce(divorce), left(left), right(right){
        if (right == NULL && !foreign) {
            this->right = new personNode;
        }
    };
    personNode(): index(-1), age(0), name("singleParent"), sex(Male), foreign(true), status(true), divorce(true), left(NULL), right(NULL) {}
};

class FamilyTree {
public:
    FamilyTree():root(NULL){};
    ~FamilyTree();
    void insertAncestor(personNode* person);//new
    void insertChild(personNode* person, personNode* parent);//parent为对应的该家庭里面的人的配偶
    void insertPartner(personNode* person, personNode* partner);//partner为配偶
    void deleteMember(personNode* person);//除去对应的符合条件的人(节点)
    vector<personNode*> queryPerson(function<bool(const personNode*)> filter);//筛选出符合条件的人
    vector<personNode*> queryPersonFromVector(vector<personNode*> data, function<bool(const personNode*)> filter);//new
    vector<personNode*> updatePerson(function<bool(const personNode*)> filter, function<bool(const personNode*)> updater);//对符合条件的人的信息进行更改
    vector<personNode*> queryParent(personNode* person);
    int count(function<bool(const personNode*)> filter);//对符合条件的人数进行统计
    void printAllPerson();
    bool empty();//new
    bool read(string filename);
	bool save(string filename); 
    //void saveToFile();
private:
    personNode* root;
};

#endif /* FamilyTree_hpp */


