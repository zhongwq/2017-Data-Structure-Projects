//
//  FamilyTreeUI.cpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017�� zhongwq. All rights reserved.
//

#include "FamilyTreeUI.hpp"
#include <limits>

FamilyTreeUI::FamilyTreeUI() {
    familyTree = new FamilyTree;
}

FamilyTreeUI::~FamilyTreeUI() {
    delete familyTree;
}

void FamilyTreeUI::printUI() {
    cout << endl;
    cout << "--------------����С����-----------------" << endl;
    cout << "0 - ��ȡ���м���" << endl;
    cout << "1 - ���뺢��" << endl;
    cout << "2 - ������ż" << endl;
    cout << "3 - ɾ����ͥ��Ա" << endl;
    cout << "4 - ���¼�ͥ��Ա��Ϣ" << endl;
    cout << "5 - ���ҷ�����Ϣ�ĳ�Ա" << endl;
    cout << "6 - ��ѯ��ͥĳ��Ա��˫��" << endl;
    cout << "7 - ��ӡ����" << endl;
    cout << "8 - ����ͳ��" << endl;
    cout << "9 - �洢����" << endl;
    cout << "10 - �뿪" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "���������ѡ��: ";
}

void FamilyTreeUI::getCommand() {
    bool flag = true;
    int command = 9;
    while (this->familyTree->empty()) {
        bool choice;
        cout << "�������еļ��׽���������(0: ��, 1: ��)? ";
        cin >> choice;
        while (cin.fail() || (choice != 0 && choice != 1)) {
        	cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "���벻�Ϸ�! ������0��1!" << endl;
            cout << "����������:";
            cin >> choice;
        }
        if (choice)
            readFile();
        else
            addAncestor();
    }
    while (flag) {
        if (this->familyTree->empty()) {
            cout << "��ͥ�����ѱ�ɾ���������Զ��˳���" << endl;
            break;
        }
        printUI();
        cin >> command;
        while (cin.fail() || (command <= 0 || command > 10)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "���벻�Ϸ�! ������1-8������!" << endl;
            cout << "����������:";
            cin >> command;
        }
        switch (command) {
            case 1:
                addChild();
                break;
            case 2:
                addWife();
                break;
            case 3:
                deletePerson();
                break;
            case 4:
                updatePersons();
                break;
            case 5:
                queryPeresons();
                break;
            case 6:
                searchParent();
                break;
            case 7:
                familyTree->printAllPerson();
                break;
            case 8:
                analyzeData();
                break;
            case 9:
                save();
                break;
            case 10:
                flag = false;
                break;
            default:
                break;
        }
    }
}

void FamilyTreeUI::readFile() {
    string file;
    cout << "Please input the name of the file you want to read: ";
    cin >> file;
    delete familyTree;
    familyTree = new FamilyTree;
    familyTree->read(file);
}  

void FamilyTreeUI::save() {
    string file;
    cout << "Please input the name of the file you want to save in: ";
    cin >> file;
    familyTree->save(file);
}

void FamilyTreeUI::addAncestor() {
    string name;
    int sexInt, age;
    Sex sex;
    bool dead;
    cout << endl;
    cout << "���������ȵ���Ϣ:" << endl;
    cout << "��ʽΪ:" << endl;
    cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "���벻�Ϸ�������������룡" << endl;
        cout << "���������ȵ���Ϣ:" << endl;
    	cout << "��ʽΪ:" << endl;
    	cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead;
    }
    sex = Sex(sexInt);
    familyTree->insertAncestor(new personNode(age, name, sex, false, dead, false));
}

void FamilyTreeUI::addChild() {
    string name, parentName;
    int sexInt, age;
    Sex sex;
    bool dead;
    cout << endl;
    cout << "������Ҫ����ĺ��ӵ���Ϣ:" << endl;
    cout << "��ʽΪ:" << endl;
    cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "���벻�Ϸ�������������룡" << endl;
        cout << "������Ҫ����ĺ��ӵ���Ϣ:" << endl;
    	cout << "��ʽΪ:" << endl;
    	cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead;
    }
    sex = Sex(sexInt);
    cout << "������ĸ�׻��߸��׵�����: ";
    cin >> parentName;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == parentName) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "�Ҳ����ø���/ĸ��!" << endl;
    else {
        personNode* child = new personNode(age, name, sex, false, dead, false);
        personNode* result = (data.size() > 1)?getOnePersonFromResult(data):data[0];
        if (result->foreign) {
            familyTree->insertChild(child, result);
        } else {
            vector<personNode*> temp;
            personNode* nowNode = result->right;
            while (nowNode) {
                temp.push_back(nowNode);
                nowNode = nowNode->right;
            }
            if (temp.size() == 1) {
                familyTree->insertChild(child, temp[0]);
            } else {
                familyTree->insertChild(child, getOnePersonFromResult(temp));
            }
        }
    }
}

void FamilyTreeUI::addWife() {
    string name, partnerName;
    int sexInt, age;
    Sex sex;
    bool dead;
    cout << endl;
    cout << "������Ҫ�������ż����Ϣ:" << endl;
    cout << "��ʽΪ:" << endl;
    cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "���벻�Ϸ�������������룡" << endl;
        cout << "������Ҫ����ĺ��ӵ���Ϣ:" << endl;
    	cout << "��ʽΪ:" << endl;
    	cout << "[����] [�Ա�(0:��, 1: Ů)] [���� (age > 0)] [�Ƿ�����(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead;
    }
    sex = Sex(sexInt);
    cout << "������ò���ڵ���ż������: ";
    cin >> partnerName;
    auto data = familyTree->queryPerson([&](const personNode* partner) {
        return ((partner->name == partnerName) && (!partner->foreign));
    });
    if (data.size() == 0)
        cout << "�Ҳ�������!" << endl;
    else if (data.size() == 1)
        familyTree->insertPartner(new personNode(age, name, sex, true, dead, false), data[0]);
    else
        familyTree->insertPartner(new personNode(age, name, sex, true, dead, false), getOnePersonFromResult(data));
}

void FamilyTreeUI::deletePerson() {
    string name;
    cout << "����������ɾ���ļ�ͥ��Ա������: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "�Ҳ�������!" << endl;
    else if (data.size() == 1) {
        familyTree->deleteMember(data[0]);
    } 
    else {
        auto personPtr = getOnePersonFromResult(data);
        familyTree->deleteMember(personPtr);
    }
}

void FamilyTreeUI::updatePersons() {
    string name;
    int age, sexInt;
    Sex sex;
    bool dead, divorced;
    personNode* person = NULL;
    cout << "��������Ҫ������Ϣ�ĳ�Ա������: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "�Ҳ�������!" << endl;
    else {
        if (data.size() > 1)
            person = getOnePersonFromResult(data);
        else
            person = data[0];
        cout << "��ǰ��Ϣ����:" << endl;
        printOnePerson(person);
        cout << "��������º����Ϣ:" << endl;
        cout << "��ʽΪ:" << endl;
        cout << "[����] [�Ա�(0:��, 1: Ů)] [����] [�Ƿ�����(0: false/1: true)] [�Ƿ������(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead >> divorced;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "�����������������룡" << endl; 
            cout << "��������º����Ϣ:" << endl;
        	cout << "��ʽΪ:" << endl;
        	cout << "[����] [�Ա�(0:��, 1: Ů)] [����] [�Ƿ�����(0: false/1: true)] [�Ƿ������(0: false/1: true)]" << endl;
            cin >> name >> sexInt >> age >> dead >> divorced;
        }
        sex = Sex(sexInt);
        person->name = name;
        person->sex = sex;
        person->age = age;
        person->status = dead;
        person->divorce = divorced;
    }
}

void FamilyTreeUI::queryPeresons() {
    auto data = familyTree->queryPerson([](const personNode* person){
        return (person->index != -1);
    });
    int choice;
    bool search[5] = {false};
    cout << "����������ṩɸѡ�ı�׼: " << endl;
    cout << "0: ����, 1: ����, 2: �Ա�, 3: �Ƿ�����, 4: �Ƿ����" << endl;
    cout << "�����ʽΪһ���Կո�Ϊ�������-1Ϊ��β�����ִ������ִ������ݼ�Ϊ��Ҫѡ��õ���׼��" << endl;
    cout << "���ӣ�0 1 4 -1 Ϊѡ�����������䡢�Ƿ������Ϊɸѡ��׼" << endl; 
    cout << "���������ѡ��: ";
    while (cin >> choice) {
    	if (cin.fail() || (choice > 4 || choice < 0)) {
    		if (choice == -1)
    			break;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "���������밴��Ҫ�������������������룡" << endl;
            cout << "���������ѡ��: ";
            continue;
        }
        search[choice] = true;
    }
    if (search[0]) {
        string name;
        cout << "��������Ҫɸѡ���˵�����: ";
        cin >> name;
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->name == name;
        });
    }
    if (search[1]) {
        int agel, ageh;
        cout << "��������Ҫɸѡ���˵�����ķ�Χ(��ʽΪǰһ�������Ǹ÷�Χ�����ޣ�������Ǹ÷�Χ�����ޣ��м��Կո����): ";
        cout << "����: 13 40 ��Ϊɸѡ13-40�����" << endl;
        cout << "�����룺"; 
        cin >> agel >> ageh;
        while (cin.fail() || (agel > ageh) || (agel < 0) || (ageh < 0)){
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "��������������Ǹ������ұ�֤ǰһ����С�ڵ��ں�һ������" << endl;
            cout << "��������Ҫɸѡ���˵�����ķ�Χ: ";
            cin >> agel >> ageh;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return (person->age >= agel && person->age <= ageh);
        });
    }
    if (search[2]) {
        int sexInt;
        cout << "��������Ҫɸѡ���˵��Ա�(0: ��, 1: Ů):";
        cin >> sexInt;
        while (cin.fail() || (sexInt != 0 && sexInt != 1)) {
            cout << "����Ƿ���������0��1��" << endl;
            cout << "��������Ҫɸѡ���˵��Ա�(0: ��, 1: Ů): ";
            cin >> sexInt;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->sex == Sex(sexInt);
        });
    }
    if (search[3]) {
        bool dead;
        cout << "��������ɸѡ�����Ƿ��Ѿ�����(0: false/1: true)? ";
        cin >> dead;
        while (cin.fail()) {
           cout << "����Ƿ���������0��1��" << endl;
           cout << "��������ɸѡ�����Ƿ��Ѿ�����(0: false/1: true)? ";
           cin >> dead;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->status == dead;
        });
    }
    if (search[4]) {
        bool divorced;
        cout << "��������ɸѡ�����Ƿ��Ѿ����(0: false/1: true)? ";
        cin >> divorced;
        while (cin.fail()) {
            cout << "����Ƿ���������0��1��" << endl;
            cout << "��������ɸѡ�����Ƿ��Ѿ�����(0: false/1: true)? ";
            cin >> divorced;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->status == divorced;
        });
    }
    cout << "ɸѡ���Ľ��Ϊ:" << endl;
    printFromVector(data);
}

void FamilyTreeUI::searchParent() {
    string name;
    cout << "�����������ѯ˫�׵ļ�ͥ��Ա������: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "�Ҳ�������!" << endl;
    else if (data.size() == 1){
        auto result = familyTree->queryParent(data[0]);
        if (result.size() == 0)
			cout << "�ó�Ա�޸�ĸ�ף�" << endl; 
        for (auto c : result) {
            cout << ((c->sex == 0)?"����: ":"ĸ��: ") << endl;
            printOnePerson(c);
        }
    } 
    else {
        auto result = familyTree->queryParent(getOnePersonFromResult(data));
        if (result.size() == 0)
			cout << "�ó�Ա�޸�ĸ�ף�" << endl; 
        for (auto c : result) {
            cout << ((c->sex == 0)?"����: ":"ĸ��: ") << endl;
            printOnePerson(c);
        }
    }
}

void FamilyTreeUI::analyzeData() {
    int choice = 0;
    cout << "----------------���ݷ�����-----------------" << endl;
    cout << "1 - ƽ������" << endl;
    cout << "2 - ƽ����������" << endl;
    cout << "3 - ��Ů����������" << endl;
    cout << "4 - ������" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "���������ѡ��: ";
    cin >> choice;
    while (cin.fail() || (choice > 4 || choice < 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "����Ƿ���������1-4�����֣�" << endl;
        cout << "�������������ѡ��: ";
        cin >> choice;
    }
    double sum = 0, maleNum, femaleNum;
    vector<personNode*> data;
    switch (choice) {
        case 1:
            sum = 0;
            data = familyTree->queryPerson([](const personNode* person) {
                return ((person->status == 0)&&(person->index != -1));
            });
            for (auto c: data)
                sum += c->age;
            cout << "������ " << data.size() << " �����ڵļ�ͥ��Ա!" << endl;
            cout << "ƽ������(������)Ϊ " << sum/data.size() << "!"<< endl;
            break;
        case 2:
            sum = 0;
            data = familyTree->queryPerson([](const personNode* person) {
                return ((person->status == 1)&&(person->index != -1));
            });
            for (auto c: data)
                sum += c->age;
            cout << "������ " << data.size() << " ���Ѿ�ȥ���ļ�ͥ��Ա!" << endl;
            if (data.size() == 0)
                cout << "��Ϊ�����������޷�����������ƽ������!" << endl;
            else
                cout << "ƽ����������Ϊ " << sum/data.size() << "!"<< endl;
            break;
        case 3:
            maleNum = familyTree->queryPerson([](const personNode* person) {
                return ((person->sex == Sex(0)) && (person->index != -1));
            }).size();
            femaleNum = familyTree->queryPerson([](const personNode* person) {
                return ((person->sex == Sex(1)) && (person->index != -1));
            }).size();
            cout << "������ " << maleNum << " ���г�Ա, " << femaleNum << " ��Ů��Ա!" << endl;
            cout << "����ռ�� " << (1.0*maleNum/(maleNum+femaleNum))*100 << "%, Ů��ռ�� " << (1.0*femaleNum/(maleNum+femaleNum))*100 << "%." << endl;
            break;
        case 4:
            cout << "�����ܹ��� " << familyTree->queryPerson([](const personNode* person){
                return (person->index != -1);
            }).size() << " ����ͥ��Ա(������ȥ���뽡�ڵ���)!" << endl;
            break;
    }
}

void FamilyTreeUI::printFromVector(vector<personNode*> result) {
    if (result.empty()) {
        cout << "û���ҵ����������ĳ�Ա!" << endl;
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        cout << "��� " << i << ":" << endl;
        printOnePerson(result[i]);
        cout << endl;
    }
}

void FamilyTreeUI::printOnePerson(personNode* person) {
    cout << "---------------------------------------" << endl;
    cout << "Index: " << person->index << endl;
    cout << "����: " << person->name << endl;
    cout << "����: " << person->age << endl;
    cout << "�Ա�: " << ((person->sex == 0)?"��":"Ů") << endl;
    cout << "�Ƿ�Ϊ�����˿�: " << ((person->foreign)?"True":"False") << endl;
    cout << "�Ƿ���ȥ��: " << ((person->status)?"Dead":"Alive") << endl;
    cout << "�Ƿ������: " << ((person->divorce)?"True":"False") << endl;
    cout << "---------------------------------------" << endl;
}

personNode* FamilyTreeUI::getOnePersonFromResult(vector<personNode*> result) {
    cout << "������ " << result.size() << " ������������ѡ��!" << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << "ѡ�� " << i << endl;
        printOnePerson(result[i]);
    }
    int choice = 0;
    cout << "���������ѡ��: ";
    cin >> choice;
    while (cin.fail() || choice < 0 || choice >= result.size()) {
        cout << "���벻�Ϸ���������0-" << result.size()-1 << "�����֣�" << endl;
        cout << "���������ѡ��: ";
        cin >> choice;
    }
    return result[choice];
}


