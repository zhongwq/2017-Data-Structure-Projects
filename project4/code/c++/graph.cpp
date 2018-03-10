#include <iostream>
#include <vector>
#include <limits.h>
#include <fstream> 
#define INFINITY INT_MAX
using namespace std;
struct place{
	string name;
	static int count;
	int id;
	string description;
	place():name(""),description(""){} 
	place(string n,string d):name(n),id(count++),description(d){}
};

class graph {
	private:
		int Manmatrix[500][500];
		int Carmatrix[500][500];
		place list[500];
		int num;
	public:
		graph():num(0){
			for(int i = 0;i < 500;i++)
				for(int j = 0;j < 500;j++)
					Manmatrix[i][j] = Carmatrix[i][j] = 0;
		}
		
		void addPlace(string name,string description){
			list[num] = place(name,description);
			num ++;
		}
		
		void deletePlace(string name){
			int j = search(name);
			list[j] = list[num - 1];
			for(int i = 0;i < num;i++){
				Manmatrix[i][j] = Manmatrix[j][i] = Manmatrix[i][num - 1];
				Carmatrix[i][j] = Carmatrix[j][i] = Carmatrix[i][num - 1];
				Manmatrix[i][num - 1] = Manmatrix[num - 1][i] = Carmatrix[num - 1][i] = Carmatrix[i][num - 1] = 0;
				if(i == j)
					Manmatrix[i][j] = Carmatrix[i][j] = 0;
			}
			num --;
		}
		
		int search(string name){
			for(int i = 0;i < num;i++){
				if(list[i].name == name)
					return i;
			}
			return -1;
		}
		
		int search(int id){
			for(int i = 0;i < num;i++){
				if(list[i].id == id)
					return i;
			}
			return -1;
		}
		
		int count(){
			return num;
		}
		
		string name(int i){
			return list[i].name;
		}
		
		void addManPath(int i,int j,int distance){
			Manmatrix[i][j] = Manmatrix[j][i] = distance;
		}
		
		void addCarPath(int i,int j,int distance){
			Carmatrix[i][j] = Carmatrix[j][i] = distance;
		}
		
		void deleteManPath(int i,int j){
			Manmatrix[i][j] = Manmatrix[j][i] = 0;
		}
		
		void deleteCarPath(int i,int j){
			Carmatrix[i][j] = Carmatrix[j][i] = 0;
		}
		
		
		vector<int> manNext(int from){
			vector<int> re;
			for(int i = 0;i < num;i++){
				if(Manmatrix[from][i] != 0)
					re.push_back(i);
			}
			return re;
		}
		
		vector<int> carNext(int from){
			vector<int> re;
			for(int i = 0;i < num;i++){
				if(Carmatrix[from][i] != 0)
					re.push_back(i);
			}
			return re;
		}
		
		vector<int> findManPath(int from,int to){
			int length[num];
			bool v[num];
			v[from] = true;
			vector<int> path[num];
			for(int i = 0;i < num;i++){
				if(i == from)
					length[i] = 0;
				else if(Manmatrix[from][i] == 0)
					length[i] = INFINITY;
				else{
					length[i] = Manmatrix[from][i];
					path[i].push_back(from);
				}
			}
			for(int j = 0;j < num;j++){
				if(j == from)
					continue;
				int min = INFINITY;
				int k = from;
				for(int i = 0;i < num;i++){
					if(!v[i] && length[i] < min){
						min = length[i];
						k = i;
					}
				}
				if(k == from)
					continue;
				v[k] = true;
				for(int i = 0;i < num;i++){
					if(!v[i] && Manmatrix[k][i] != 0 && (min + Manmatrix[k][i]) < length[i]){
						length[i] = min + Manmatrix[k][i];
						path[i] = path[k];
						path[i].push_back(k);
					}
				}
			}
			return path[to];
		}
		
		vector<int> findCarPath(int from,int to){
			int length[num];
			bool v[num];
			v[from] = true;
			vector<int> path[num];
			for(int i = 0;i < num;i++){
				if(i == from)
					length[i] = 0;
				else if(Carmatrix[from][i] == 0)
					length[i] = INFINITY;
				else{
					length[i] = Carmatrix[from][i];
					path[i].push_back(from);
				}
			}
			for(int j = 0;j < num;j++){
				if(j == from)
					continue;
				int min = INFINITY;
				int k = from;
				for(int i = 0;i < num;i++){
					if(!v[i] && length[i] < min){
						min = length[i];
						k = i;
					}
				}
				if(k == from)
					continue;
				v[k] = true;
				for(int i = 0;i < num;i++){
					if(!v[i] && Carmatrix[k][i] != 0 && (min + Carmatrix[k][i]) < length[i]){
						length[i] = min + Carmatrix[k][i];
						path[i] = path[k];
						path[i].push_back(k);
					}
				}
			}
			return path[to];
		}
		
		int manPath(int from,int to){
			return Manmatrix[from][to];
		}
		
		int carPath(int from,int to){
			return Carmatrix[from][to];
		}
		
		place getPlace(int i){
			return list[i];
		}
		
		void print(){
			for(int i = 0;i < num;i++)
				cout << list[i].name << endl; 
		}
		
		bool save(string filename){
			ofstream of(filename);
			if(!of)
				return false;
			of << num << endl;
			for(int i = 0;i < num;i++){
				of << list[i].name << endl;
				of << list[i].description << endl;
			}
			for(int i = 0;i < num;i++){
				for(int j = 0;j < num;j++){
					of << Manmatrix[i][j] << " ";
				}
				of << endl;
			}
			for(int i = 0;i < num;i++){
				for(int j = 0;j < num;j++){
					of << Carmatrix[i][j] << " ";
				}
				of << endl;
			}
			of.close();
			return true;
		}
		
		bool read(string filename){
			ifstream file(filename);
			if(!file)
				return false;
			file >> num;
			string name,description;
			getline(file,name);
			for(int i = 0;i < num;i++){
				getline(file,name);
				getline(file,description);
				list[i] = place(name,description);
			}
			for(int i = 0;i < num;i++)
				for(int j = 0;j < num;j++)
					file >> Manmatrix[i][j];
			for(int i = 0;i < num;i++)
				for(int j = 0;j < num;j++)
					file >> Carmatrix[i][j];
			file.close();
			return true;
		}
};










