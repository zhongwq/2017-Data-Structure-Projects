#include <iostream>
#include <limits>
#include "graph.cpp"

class UI {
	private:
		graph g;
	public:
		UI(){}
		
		void printUI(){
			cout << endl;
   			cout << "-------------------����------------------" << endl;
    		cout << "1 - ��ӵص�" << endl;
    		cout << "2 - ��ӻ��޸Ĳ���·��" << endl;
    		cout << "3 - ��ӻ��޸ĳ���·��" << endl;
	    	cout << "4 - ɾ���ص�" << endl;
    		cout << "5 - ɾ������·��" << endl;
    		cout << "6 - ɾ������·��" << endl;
	    	cout << "7 - ��ѯ�ص���Ϣ" << endl;
	    	cout << "8 - Ѱ����̲���·��" << endl;
	    	cout << "9 - Ѱ����̳���·��" << endl;
	    	cout << "10 - ������еص�" << endl;
	    	cout << "11 - ��ȡ���е�ͼ" << endl;
	    	cout << "12 - �洢��ͼ" << endl;
 	 		cout << "13 - �뿪" << endl;
   		 	cout << "-----------------------------------------" << endl;
   		 	cout << "���������ѡ��: ";
		}
		
		void getCommand() {
	       bool choice;
	       cout << "�������е�ͼ����������(0: ��, 1: ��)? ";
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
			bool flag = true;
			int command; 
		    while (flag) {
    			printUI();
	        	cin >> command;
        		while (cin.fail() || (command <= 0 || command > 13)) {
 		        	cin.clear();
		        	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
   		    		cout << "���벻�Ϸ�! ������1~13������!" << endl;
    	    		cout << "����������:";
        			cin >> command;
    			}
        		switch (command) {
		    		case 1:
        	   		 	addPlace();
            			break;
        			case 2:
            			addManPath();
            			break;
        			case 3:
            			addCarPath();
            			break;
        			case 4:
            			deletePlace();
            			break;
        			case 5:
            			deleteManPath();
            			break;
        			case 6:
            			deleteCarPath();
            			break;
        			case 7:
            			queryPlace();
            			break;
        			case 8:
           		 		findManPath();
            			break;
        			case 9:
            			findCarPath();
            			break;
        			case 10:
            			g.print();
            			break;
            		case 11:
            			readFile();
            			break;
            		case 12:
            			save();
            			break;
            		case 13:
            			flag = false;
            			break;
        			default:
            			break;
    			}
			}
    	} 
    	
    	void addPlace(){
    		string name,description;
    		cout << "������ص����ƣ�" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid != -1){
				cout << "�˵ص�����ӣ�" << endl;
				cout << "������ص����ƣ�" << endl;
				cin >> name;
				valid = g.search(name);
			}
			getline(cin,description);
			cout << "�������̵Ľ��ܣ�" << endl;
			getline(cin,description);
			g.addPlace(name,description);
			cout << "�ɹ���ӣ�" << endl;
    	}
    	
    	void addManPath(){
			int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		} 
    		string from,to;
    		int dis;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		cout << "��������루��������" << endl;
    		cin >> dis;
    		while(cin.fail() || dis <= 0){
    			cin.clear();
    			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    			cout << "���벻�Ϸ����������룡" << endl;
    			cout << "��������루��������" << endl;
    			cin >> dis;
    		}
    		g.addManPath(i,j,dis);
    		cout << "�ɹ���ӣ�" << endl;
    	}
    	
    	void addCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		}
    		string from,to;
    		int dis;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		cout << "��������루��������" << endl;
    		cin >> dis;
    		while(cin.fail() || dis <= 0){
    			cin.clear();
    			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    			cout << "���벻�Ϸ����������룡" << endl;
    			cout << "��������루��������" << endl;
    			cin >> dis;
    		}
    		g.addCarPath(i,j,dis);
    		cout << "�ɹ���ӣ�" << endl;
    	}
    	
    	void deletePlace(){
    		int num = g.count();
    		if(num == 0){
    			cout << "û�еص����ɾ����"<< endl;
    			return;
    		}
    		string name;
    		cout << "������ص����ƣ�" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid == -1){
				cout << "�˵ص㲻���ڣ�" << endl;
				cout << "������ص����ƣ�" << endl;
				cin >> name;
				valid = g.search(name);
			}
			g.deletePlace(name);
			cout << "�ɹ�ɾ��" << endl;
    	}
    	
    	void deleteManPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		if(g.manPath(i,j) == 0){
    			cout << "�������ص�֮��û��·����" << endl;
    			return;
    		}
    		g.deleteManPath(i,j);
    		cout << "�ɹ�ɾ��" << endl;
    	}
    	
    	void deleteCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		if(g.carPath(i,j) == 0){
    			cout << "�������ص�֮��û��·����" << endl;
    			return;
    		} 
    		g.deleteCarPath(i,j);
    		cout << "�ɹ�ɾ��" << endl;
    	}
    	
    	void queryPlace(){
    		int num = g.count();
    		if(num == 0){
    			cout << "�޵ص�ɲ�ѯ��"<< endl;
    			return;
    		}
    		string name;
    		cout << "������ص����ƣ�" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid == -1){
				cout << "�˵ص㲻���ڣ�" << endl;
				cout << "������ص����ƣ�" << endl;
				cin >> name;
				valid = g.search(name);
			}
			place temp = g.getPlace(g.search(name));
			vector<int> manNext = g.manNext(valid);
			vector<int> carNext = g.carNext(valid);
			cout << "-----------------------------------------" << endl;
			cout << "���ƣ�" << temp.name << endl;
			cout << "��ţ�" << temp.id << endl;
			cout << "������" << temp.description << endl;
			cout << "�ٽ�(����)������";
			if(manNext.size() == 0)
				cout << "��" << endl;
			for(int i = 0;i < manNext.size();i++){
				if(i != 0)
					cout << "                ";
				cout << g.name(manNext[i]) << " ���룺" << g.manPath(manNext[i],valid) << endl; 
			} 
			cout << "�ٽ�(����)������";
			if(carNext.size() == 0)
				cout << "��" << endl;
			for(int i = 0;i < carNext.size();i++){
				if(i != 0)
					cout << "                ";
				cout << g.name(carNext[i]) << " ���룺" << g.carPath(carNext[i],valid) << endl; 
			}
			cout << "-----------------------------------------" << endl;
    	}
    	
    	void findManPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		vector<int> path = g.findManPath(i,j);
    		if(path.size() == 0){
    			cout << "��·���ߣ�" << endl;
    			return;
    		}
    		int l = 0;
    		if(path.size() == 1){
    			cout << from << "--" << g.manPath(i,j) << "->" << to << endl;
    			cout << "�ܳ�" << g.manPath(i,j) << endl;
    			return;
    		}
    		for(int i = 0;i < path.size();i++){
    			if(i == 0)
    				cout << g.name(path[i]) << "--";
    			else if(i != path.size() - 1){
    				l += g.manPath(path[i-1],path[i]);
    				cout << g.manPath(path[i-1],path[i]) << "->" << g.name(path[i]) << "--";
    			}
    			else{
    				l += g.manPath(path[i-1],path[i]);
    				cout << g.manPath(path[i-1],path[i]) << "->" << g.name(path[i]);
    			}
    		}
    		l += g.manPath(path[path.size() -1],j);
    		cout << "--" << g.manPath(path[path.size() -1],j) << "->" << g.name(j) << endl;
    		cout << "�ܳ�" << l << endl; 
    	}
    	
    	void findCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "�ص�С��2����"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "������ص�1���ƣ�" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����1��" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "������ص�2���ƣ�" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "��ص�1�����ظ���" << endl;
					cout << "������ص�����2��" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "�����ڴ˵ص�" << endl;
				cout << "������ص�����2��" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		vector<int> path = g.findCarPath(i,j);
    		if(path.size() == 0){
    			cout << "��·���ߣ�" << endl;
    			return;
    		}
    		int l = 0;
    		if(path.size() == 1){
    			cout << from << "--" << g.carPath(i,j) << "->" << to << endl;
    			cout << "�ܳ�" << g.carPath(i,j) << endl;
    			return;
    		}
    		for(int i = 0;i < path.size();i++){
    			if(i == 0)
    				cout << g.name(path[i]) << "--";
    			else if(i != path.size() - 1){
    				l += g.manPath(path[i-1],path[i]);
    				cout << g.carPath(path[i-1],path[i]) << "->" << g.name(path[i]) << "--";
    			}
    			else{
    				l += g.carPath(path[i-1],path[i]);
    				cout << g.carPath(path[i-1],path[i]) << "->" << g.name(path[i]);
    			}
    		}
    		l += g.carPath(path[path.size() -1],j);
    		cout << "--" << g.carPath(path[path.size() -1],j) << "->" << g.name(j) << endl;
    		cout << "�ܳ�" << l << endl; 
    	}
    	
    	void save(){
    		string file;
    		cout << "�������ļ�����" << endl;
    		cin >> file;
    		g.save(file);
			cout << "�ɹ��洢��" << endl; 
    	}
    	
    	void readFile(){
    		string filename;
    		cout << "�������ļ�����" << endl;
			cin >> filename;
			if(g.read(filename))
				cout << "�ɹ����룡" << endl;
			else
				cout << "�ļ��������ڣ�����ʧ�ܣ�" << endl;
    	}
    	
};


