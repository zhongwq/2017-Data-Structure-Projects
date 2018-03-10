//
//  FamilyTree.hpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017�� zhongwq. All rights reserved.
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
    static int indexNum;//��̬������Ҫ��ʼ��
    int index;
    int age;
    string name;
    Sex sex;
    bool foreign;
    //vector<string> extraInfo;
    bool status;//�Ƿ�����
    bool divorce;
    personNode* left;//��߶��ڸýڵ�Ϊ�ֵܽ��ù�ϵ
    personNode* right;//�ұ߶��ڸýڵ�Ϊ��ż��..��ʹ����Ҳ���¼�ڲ᣺��
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
    void insertChild(personNode* person, personNode* parent);//parentΪ��Ӧ�ĸü�ͥ������˵���ż
    void insertPartner(personNode* person, personNode* partner);//partnerΪ��ż
    void deleteMember(personNode* person);//��ȥ��Ӧ�ķ�����������(�ڵ�)
    vector<personNode*> queryPerson(function<bool(const personNode*)> filter);//ɸѡ��������������
    vector<personNode*> queryPersonFromVector(vector<personNode*> data, function<bool(const personNode*)> filter);//new
    vector<personNode*> updatePerson(function<bool(const personNode*)> filter, function<bool(const personNode*)> updater);//�Է����������˵���Ϣ���и���
    vector<personNode*> queryParent(personNode* person);
    int count(function<bool(const personNode*)> filter);//�Է�����������������ͳ��
    void printAllPerson();
    bool empty();//new
    bool read(string filename);
	bool save(string filename); 
    //void saveToFile();
private:
    personNode* root;
};

#endif /* FamilyTree_hpp */


