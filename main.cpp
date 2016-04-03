#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include<string>

using namespace std;

void readWeights(string fileName, vector<node<double> > &weights);
void readPath(string fileName, vector<Path> *path_vec);

int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Enter the weights file name: ";
	cin >> input; 
	node<double>* first;
	vector<Path> path_vec;
	vector<node<double> > weights;
	readWeights(input, weights);
	cout << "Weights created" << endl;
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);
	
	double totalWeight;
	
	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;
		totalWeight += weights[i].get_weight();
	}
	cout << "totalWeight: " << totalWeight << endl;


	// for(double i = 0; i < pathSize; i++){
	// 	cout << "Item " << i << " is "
	// 		 << path_vec[i].get_data()
	// 		 << " with a path of "  
	// 		 << path_vec[i].get_path() << endl;
	// }
	cout << "End!" << endl;	
	return 0;
}

void readWeights(string fileName, vector<node<double> > &weights){
	//for line in file
	ifstream infile;
	char key;  			//first character is the data for node
	double weight;
	//second string is weight of character 
	infile.open(fileName.c_str());
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		//cout << "This line: " << temp << endl;
		if(temp != ""){
			key = temp[0];
			//cout << "Key: " << key << endl;
			weight = atof(temp.substr(2,temp.size()-1).c_str());
			//cout << "weight: " << weight<<endl;
			node<double> tempnode = node<double>(weight, key);
		//	cout << "About to push" << endl;
			weights.push_back(tempnode);
		}
	}
}

void readPath(string fileName, vector<Path> *path_vec, int pathSize){
	//for line in file
	ifstream infile;
	//sting key;		//first character is the data for node
	double 	pathBinary = 0;		//second string is path of character 
	infile.open(fileName.c_str());
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		// cout << "This line: " << temp << endl;
		if(temp != " "){
			string key = temp.substr(0, 1);
			// cout << "Key: " << key << endl;
			//pathBinary = atof(temp.substr(2).c_str());
			pathBinary= atof(temp.substr(1).c_str());
			// cout <<setprecision(4) << "pathBinary: " << pathBinary <<endl;
			Path tempPath = Path(key, pathBinary);
			path_vec->push_back(tempPath);
			pathSize ++;
		}
		// cout <<"Path size is " << pathSize<<endl;
	}	
}
