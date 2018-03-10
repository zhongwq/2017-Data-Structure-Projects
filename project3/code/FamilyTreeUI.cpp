//
//  FamilyTreeUI.cpp
//  FamilyTree
//
//  Created by zhongwq on 2017/11/29.
//  Copyright ? 2017年 zhongwq. All rights reserved.
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
    cout << "--------------家谱小程序-----------------" << endl;
    cout << "0 - 读取已有家谱" << endl;
    cout << "1 - 插入孩子" << endl;
    cout << "2 - 插入配偶" << endl;
    cout << "3 - 删除家庭成员" << endl;
    cout << "4 - 更新家庭成员信息" << endl;
    cout << "5 - 查找符合信息的成员" << endl;
    cout << "6 - 查询家庭某成员的双亲" << endl;
    cout << "7 - 打印家谱" << endl;
    cout << "8 - 数据统计" << endl;
    cout << "9 - 存储家谱" << endl;
    cout << "10 - 离开" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "请输入你的选择: ";
}

void FamilyTreeUI::getCommand() {
    bool flag = true;
    int command = 9;
    while (this->familyTree->empty()) {
        bool choice;
        cout << "你有已有的家谱进行输入吗(0: 无, 1: 有)? ";
        cin >> choice;
        while (cin.fail() || (choice != 0 && choice != 1)) {
        	cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "输入不合法! 请输入0或1!" << endl;
            cout << "请重新输入:";
            cin >> choice;
        }
        if (choice)
            readFile();
        else
            addAncestor();
    }
    while (flag) {
        if (this->familyTree->empty()) {
            cout << "家庭祖先已被删除！程序自动退出！" << endl;
            break;
        }
        printUI();
        cin >> command;
        while (cin.fail() || (command <= 0 || command > 10)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "输入不合法! 请输入1-8的数字!" << endl;
            cout << "请重新输入:";
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
    cout << "请输入祖先的信息:" << endl;
    cout << "格式为:" << endl;
    cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入不合法，请检查你的输入！" << endl;
        cout << "请输入祖先的信息:" << endl;
    	cout << "格式为:" << endl;
    	cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
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
    cout << "请输入要插入的孩子的信息:" << endl;
    cout << "格式为:" << endl;
    cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入不合法，请检查你的输入！" << endl;
        cout << "请输入要插入的孩子的信息:" << endl;
    	cout << "格式为:" << endl;
    	cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead;
    }
    sex = Sex(sexInt);
    cout << "请输入母亲或者父亲的名字: ";
    cin >> parentName;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == parentName) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "找不到该父亲/母亲!" << endl;
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
    cout << "请输入要插入的配偶的信息:" << endl;
    cout << "格式为:" << endl;
    cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
    cin >> name >> sexInt >> age >> dead;
    while (cin.fail() || age <= 0 || (sexInt != 0 && sexInt != 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入不合法，请检查你的输入！" << endl;
        cout << "请输入要插入的孩子的信息:" << endl;
    	cout << "格式为:" << endl;
    	cout << "[名字] [性别(0:男, 1: 女)] [年龄 (age > 0)] [是否死亡(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead;
    }
    sex = Sex(sexInt);
    cout << "请输入该插入节点配偶的名字: ";
    cin >> partnerName;
    auto data = familyTree->queryPerson([&](const personNode* partner) {
        return ((partner->name == partnerName) && (!partner->foreign));
    });
    if (data.size() == 0)
        cout << "找不到此人!" << endl;
    else if (data.size() == 1)
        familyTree->insertPartner(new personNode(age, name, sex, true, dead, false), data[0]);
    else
        familyTree->insertPartner(new personNode(age, name, sex, true, dead, false), getOnePersonFromResult(data));
}

void FamilyTreeUI::deletePerson() {
    string name;
    cout << "请输入你想删除的家庭成员的名字: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "找不到此人!" << endl;
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
    cout << "请输入你要更新信息的成员的名称: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "找不到此人!" << endl;
    else {
        if (data.size() > 1)
            person = getOnePersonFromResult(data);
        else
            person = data[0];
        cout << "当前信息如下:" << endl;
        printOnePerson(person);
        cout << "请输入更新后的信息:" << endl;
        cout << "格式为:" << endl;
        cout << "[名字] [性别(0:男, 1: 女)] [年龄] [是否死亡(0: false/1: true)] [是否已离婚(0: false/1: true)]" << endl;
        cin >> name >> sexInt >> age >> dead >> divorced;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "输入有误，请重新输入！" << endl; 
            cout << "请输入更新后的信息:" << endl;
        	cout << "格式为:" << endl;
        	cout << "[名字] [性别(0:男, 1: 女)] [年龄] [是否死亡(0: false/1: true)] [是否已离婚(0: false/1: true)]" << endl;
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
    cout << "这里有五个提供筛选的标准: " << endl;
    cout << "0: 姓名, 1: 年龄, 2: 性别, 3: 是否死亡, 4: 是否离婚" << endl;
    cout << "输入格式为一串以空格为间隔，以-1为结尾的数字串，数字串的内容即为你要选择得到标准。" << endl;
    cout << "例子：0 1 4 -1 为选择姓名、年龄、是否离婚作为筛选标准" << endl; 
    cout << "请输入你的选择: ";
    while (cin >> choice) {
    	if (cin.fail() || (choice > 4 || choice < 0)) {
    		if (choice == -1)
    			break;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "输入有误，请按照要求检查你的输入后重新输入！" << endl;
            cout << "请输入你的选择: ";
            continue;
        }
        search[choice] = true;
    }
    if (search[0]) {
        string name;
        cout << "请输入你要筛选的人的姓名: ";
        cin >> name;
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->name == name;
        });
    }
    if (search[1]) {
        int agel, ageh;
        cout << "请输入你要筛选的人的年龄的范围(格式为前一个数字是该范围的下限，后面的是该范围的上限，中间以空格隔开): ";
        cout << "例子: 13 40 即为筛选13-40岁的人" << endl;
        cout << "请输入："; 
        cin >> agel >> ageh;
        while (cin.fail() || (agel > ageh) || (agel < 0) || (ageh < 0)){
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "输入有误！请输入非负整数且保证前一个数小于等于后一个数！" << endl;
            cout << "请输入你要筛选的人的年龄的范围: ";
            cin >> agel >> ageh;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return (person->age >= agel && person->age <= ageh);
        });
    }
    if (search[2]) {
        int sexInt;
        cout << "请输入你要筛选的人的性别(0: 男, 1: 女):";
        cin >> sexInt;
        while (cin.fail() || (sexInt != 0 && sexInt != 1)) {
            cout << "输入非法！请输入0或1！" << endl;
            cout << "请输入你要筛选的人的性别(0: 男, 1: 女): ";
            cin >> sexInt;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->sex == Sex(sexInt);
        });
    }
    if (search[3]) {
        bool dead;
        cout << "请问你想筛选的人是否已经过世(0: false/1: true)? ";
        cin >> dead;
        while (cin.fail()) {
           cout << "输入非法！请输入0或1！" << endl;
           cout << "请问你想筛选的人是否已经过世(0: false/1: true)? ";
           cin >> dead;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->status == dead;
        });
    }
    if (search[4]) {
        bool divorced;
        cout << "请问你想筛选的人是否已经离婚(0: false/1: true)? ";
        cin >> divorced;
        while (cin.fail()) {
            cout << "输入非法！请输入0或1！" << endl;
            cout << "请问你想筛选的人是否已经过世(0: false/1: true)? ";
            cin >> divorced;
        }
        data = familyTree->queryPersonFromVector(data, [&](const personNode* person) {
            return person->status == divorced;
        });
    }
    cout << "筛选出的结果为:" << endl;
    printFromVector(data);
}

void FamilyTreeUI::searchParent() {
    string name;
    cout << "请输入你想查询双亲的家庭成员的名字: ";
    cin >> name;
    auto data = familyTree->queryPerson([&](const personNode* person) {
        return ((person->name == name) && (person->index != -1));
    });
    if (data.size() == 0)
        cout << "找不到此人!" << endl;
    else if (data.size() == 1){
        auto result = familyTree->queryParent(data[0]);
        if (result.size() == 0)
			cout << "该成员无父母亲！" << endl; 
        for (auto c : result) {
            cout << ((c->sex == 0)?"父亲: ":"母亲: ") << endl;
            printOnePerson(c);
        }
    } 
    else {
        auto result = familyTree->queryParent(getOnePersonFromResult(data));
        if (result.size() == 0)
			cout << "该成员无父母亲！" << endl; 
        for (auto c : result) {
            cout << ((c->sex == 0)?"父亲: ":"母亲: ") << endl;
            printOnePerson(c);
        }
    }
}

void FamilyTreeUI::analyzeData() {
    int choice = 0;
    cout << "----------------数据分析仪-----------------" << endl;
    cout << "1 - 平均年龄" << endl;
    cout << "2 - 平均死亡年龄" << endl;
    cout << "3 - 男女比例及人数" << endl;
    cout << "4 - 总人数" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "请输入你的选择: ";
    cin >> choice;
    while (cin.fail() || (choice > 4 || choice < 1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "输入非法！请输入1-4的数字！" << endl;
        cout << "请重新输入你的选择: ";
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
            cout << "这里有 " << data.size() << " 个健在的家庭成员!" << endl;
            cout << "平均年龄(存活的人)为 " << sum/data.size() << "!"<< endl;
            break;
        case 2:
            sum = 0;
            data = familyTree->queryPerson([](const personNode* person) {
                return ((person->status == 1)&&(person->index != -1));
            });
            for (auto c: data)
                sum += c->age;
            cout << "这里有 " << data.size() << " 个已经去世的家庭成员!" << endl;
            if (data.size() == 0)
                cout << "因为无人死亡，无法计算死亡的平均年龄!" << endl;
            else
                cout << "平均死亡年龄为 " << sum/data.size() << "!"<< endl;
            break;
        case 3:
            maleNum = familyTree->queryPerson([](const personNode* person) {
                return ((person->sex == Sex(0)) && (person->index != -1));
            }).size();
            femaleNum = familyTree->queryPerson([](const personNode* person) {
                return ((person->sex == Sex(1)) && (person->index != -1));
            }).size();
            cout << "这里有 " << maleNum << " 个男成员, " << femaleNum << " 个女成员!" << endl;
            cout << "男性占比 " << (1.0*maleNum/(maleNum+femaleNum))*100 << "%, 女性占比 " << (1.0*femaleNum/(maleNum+femaleNum))*100 << "%." << endl;
            break;
        case 4:
            cout << "这里总共有 " << familyTree->queryPerson([](const personNode* person){
                return (person->index != -1);
            }).size() << " 个家庭成员(包括已去世与健在的人)!" << endl;
            break;
    }
}

void FamilyTreeUI::printFromVector(vector<personNode*> result) {
    if (result.empty()) {
        cout << "没有找到符合条件的成员!" << endl;
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        cout << "结果 " << i << ":" << endl;
        printOnePerson(result[i]);
        cout << endl;
    }
}

void FamilyTreeUI::printOnePerson(personNode* person) {
    cout << "---------------------------------------" << endl;
    cout << "Index: " << person->index << endl;
    cout << "姓名: " << person->name << endl;
    cout << "年龄: " << person->age << endl;
    cout << "性别: " << ((person->sex == 0)?"男":"女") << endl;
    cout << "是否为外来人口: " << ((person->foreign)?"True":"False") << endl;
    cout << "是否已去世: " << ((person->status)?"Dead":"Alive") << endl;
    cout << "是否已离婚: " << ((person->divorce)?"True":"False") << endl;
    cout << "---------------------------------------" << endl;
}

personNode* FamilyTreeUI::getOnePersonFromResult(vector<personNode*> result) {
    cout << "这里有 " << result.size() << " 个符合条件的选项!" << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << "选项 " << i << endl;
        printOnePerson(result[i]);
    }
    int choice = 0;
    cout << "请输入你的选择: ";
    cin >> choice;
    while (cin.fail() || choice < 0 || choice >= result.size()) {
        cout << "输入不合法！请输入0-" << result.size()-1 << "的数字！" << endl;
        cout << "请输入你的选择: ";
        cin >> choice;
    }
    return result[choice];
}


