//
//  FamilyTreeUI.hpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017�� zhongwq. All rights reserved.
//

#ifndef FamilyTreeUI_hpp
#define FamilyTreeUI_hpp

#include <iostream>
#include "FamilyTree.hpp"
using namespace std;

class FamilyTreeUI {
public:
    FamilyTreeUI();
    ~FamilyTreeUI();
    void readFile();
    void save();
    void printUI();
    void getCommand();
    void addAncestor();
    void addChild();
    void addWife();
    void updatePersons();
    void deletePerson();
    void searchParent();
    void queryPeresons();
    void analyzeData();
    void printOnePerson(personNode* person);
    personNode* getOnePersonFromResult(vector<personNode*> result);
    void printFromVector(vector<personNode*> result);
    //...�����Ա,��������,������ͳ�ƣ����³�Ա��Ϣ��ɾ����Ա����ѯ��Ա,��ӡ
private:
    FamilyTree* familyTree;
};


#endif /* FamilyTreeUI_hpp */


