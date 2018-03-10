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
   			cout << "-------------------导游------------------" << endl;
    		cout << "1 - 添加地点" << endl;
    		cout << "2 - 添加或修改步行路径" << endl;
    		cout << "3 - 添加或修改车行路径" << endl;
	    	cout << "4 - 删除地点" << endl;
    		cout << "5 - 删除步行路径" << endl;
    		cout << "6 - 删除车行路径" << endl;
	    	cout << "7 - 查询地点信息" << endl;
	    	cout << "8 - 寻找最短步行路径" << endl;
	    	cout << "9 - 寻找最短车行路径" << endl;
	    	cout << "10 - 输出所有地点" << endl;
	    	cout << "11 - 读取已有地图" << endl;
	    	cout << "12 - 存储地图" << endl;
 	 		cout << "13 - 离开" << endl;
   		 	cout << "-----------------------------------------" << endl;
   		 	cout << "请输入你的选择: ";
		}
		
		void getCommand() {
	       bool choice;
	       cout << "你有已有地图进行输入吗(0: 无, 1: 有)? ";
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
			bool flag = true;
			int command; 
		    while (flag) {
    			printUI();
	        	cin >> command;
        		while (cin.fail() || (command <= 0 || command > 13)) {
 		        	cin.clear();
		        	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
   		    		cout << "输入不合法! 请输入1~13的数字!" << endl;
    	    		cout << "请重新输入:";
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
    		cout << "请输入地点名称：" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid != -1){
				cout << "此地点已添加！" << endl;
				cout << "请输入地点名称：" << endl;
				cin >> name;
				valid = g.search(name);
			}
			getline(cin,description);
			cout << "请输入简短的介绍：" << endl;
			getline(cin,description);
			g.addPlace(name,description);
			cout << "成功添加！" << endl;
    	}
    	
    	void addManPath(){
			int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		} 
    		string from,to;
    		int dis;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		cout << "请输入距离（正整数）" << endl;
    		cin >> dis;
    		while(cin.fail() || dis <= 0){
    			cin.clear();
    			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    			cout << "输入不合法，请检查输入！" << endl;
    			cout << "请输入距离（正整数）" << endl;
    			cin >> dis;
    		}
    		g.addManPath(i,j,dis);
    		cout << "成功添加！" << endl;
    	}
    	
    	void addCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		}
    		string from,to;
    		int dis;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		cout << "请输入距离（正整数）" << endl;
    		cin >> dis;
    		while(cin.fail() || dis <= 0){
    			cin.clear();
    			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    			cout << "输入不合法，请检查输入！" << endl;
    			cout << "请输入距离（正整数）" << endl;
    			cin >> dis;
    		}
    		g.addCarPath(i,j,dis);
    		cout << "成功添加！" << endl;
    	}
    	
    	void deletePlace(){
    		int num = g.count();
    		if(num == 0){
    			cout << "没有地点可以删除！"<< endl;
    			return;
    		}
    		string name;
    		cout << "请输入地点名称：" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid == -1){
				cout << "此地点不存在！" << endl;
				cout << "请输入地点名称：" << endl;
				cin >> name;
				valid = g.search(name);
			}
			g.deletePlace(name);
			cout << "成功删除" << endl;
    	}
    	
    	void deleteManPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		if(g.manPath(i,j) == 0){
    			cout << "这两个地点之间没有路径！" << endl;
    			return;
    		}
    		g.deleteManPath(i,j);
    		cout << "成功删除" << endl;
    	}
    	
    	void deleteCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		if(g.carPath(i,j) == 0){
    			cout << "这两个地点之间没有路径！" << endl;
    			return;
    		} 
    		g.deleteCarPath(i,j);
    		cout << "成功删除" << endl;
    	}
    	
    	void queryPlace(){
    		int num = g.count();
    		if(num == 0){
    			cout << "无地点可查询！"<< endl;
    			return;
    		}
    		string name;
    		cout << "请输入地点名称：" << endl;
			cin >> name;
			int valid = g.search(name);
			while(valid == -1){
				cout << "此地点不存在！" << endl;
				cout << "请输入地点名称：" << endl;
				cin >> name;
				valid = g.search(name);
			}
			place temp = g.getPlace(g.search(name));
			vector<int> manNext = g.manNext(valid);
			vector<int> carNext = g.carNext(valid);
			cout << "-----------------------------------------" << endl;
			cout << "名称：" << temp.name << endl;
			cout << "编号：" << temp.id << endl;
			cout << "描述：" << temp.description << endl;
			cout << "临近(步行)地区：";
			if(manNext.size() == 0)
				cout << "无" << endl;
			for(int i = 0;i < manNext.size();i++){
				if(i != 0)
					cout << "                ";
				cout << g.name(manNext[i]) << " 距离：" << g.manPath(manNext[i],valid) << endl; 
			} 
			cout << "临近(车行)地区：";
			if(carNext.size() == 0)
				cout << "无" << endl;
			for(int i = 0;i < carNext.size();i++){
				if(i != 0)
					cout << "                ";
				cout << g.name(carNext[i]) << " 距离：" << g.carPath(carNext[i],valid) << endl; 
			}
			cout << "-----------------------------------------" << endl;
    	}
    	
    	void findManPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		vector<int> path = g.findManPath(i,j);
    		if(path.size() == 0){
    			cout << "无路可走！" << endl;
    			return;
    		}
    		int l = 0;
    		if(path.size() == 1){
    			cout << from << "--" << g.manPath(i,j) << "->" << to << endl;
    			cout << "总长" << g.manPath(i,j) << endl;
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
    		cout << "总长" << l << endl; 
    	}
    	
    	void findCarPath(){
    		int num = g.count();
    		if(num < 2){
    			cout << "地点小于2个！"<< endl;
    			return;
    		}
    		string from,to;
    		cout << "请输入地点1名称：" << endl;
    		cin >> from;
    		int i = g.search(from);
    		while(i == -1){
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称1：" << endl;
				cin >> from;
				i = g.search(from); 
    		}
    		cout << "请输入地点2名称：" << endl;
    		cin >> to;
			int j = g.search(to);
			while(j == -1 || to == from){
				if(to == from){
					cout << "与地点1名称重复！" << endl;
					cout << "请输入地点名称2：" << endl;
					cin >> to;
					j = g.search(from);
					continue;
				}
    			cout << "不存在此地点" << endl;
				cout << "请输入地点名称2：" << endl;
				cin >> to;
				j = g.search(to); 
    		}
    		vector<int> path = g.findCarPath(i,j);
    		if(path.size() == 0){
    			cout << "无路可走！" << endl;
    			return;
    		}
    		int l = 0;
    		if(path.size() == 1){
    			cout << from << "--" << g.carPath(i,j) << "->" << to << endl;
    			cout << "总长" << g.carPath(i,j) << endl;
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
    		cout << "总长" << l << endl; 
    	}
    	
    	void save(){
    		string file;
    		cout << "请输入文件名：" << endl;
    		cin >> file;
    		g.save(file);
			cout << "成功存储！" << endl; 
    	}
    	
    	void readFile(){
    		string filename;
    		cout << "请输入文件名：" << endl;
			cin >> filename;
			if(g.read(filename))
				cout << "成功导入！" << endl;
			else
				cout << "文件名不存在！导入失败！" << endl;
    	}
    	
};


