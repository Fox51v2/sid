#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include<string>
#include<algorithm>

using namespace std;

void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight);
void readPath(string fileName, vector<Path> *path_vec);
void sortVector(vector<node<double> > &weights);
void printTree(node<double>* root);

int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Enter the weights file name: ";
	cin >> input; 
	node<double>* first;
	vector<Path> path_vec;
	vector<node<double> > weights;
	double totalWeight = 0.0;
	readWeights(input, weights, totalWeight);
	cout << "Weights created" << endl;
	int sizeOfTree = weights.size();
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);
	
	//double totalWeight;
	
	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;
		//totalWeight += weights[i].get_weight();
	}
	cout << "totalWeight: " << totalWeight << endl;
	
	sortVector(weights);
	
	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;
		//totalWeight += weights[i].get_weight();
	}


	node<double>* root;
	double tempWeight = 0.0;
	node<double>* lastConnection;


	for(int i = 0; i < sizeOfTree; i++){
		if(i == 0){
			node<double>* temp = new node<double>(weights[i].get_weight(),weights[i].get_char());
			root = temp;
			tempWeight += temp->get_weight();
		}
		else{
			node<double>* temp = new node<double>(weights[i].get_weight(),weights[i].get_char());
			lastConnection = new node<double>(root->get_weight() + temp->get_weight(), root, temp);
			root = lastConnection;
			tempWeight += temp->get_weight();
		}
	}
	cout << "Stuff set?" << endl;

	printTree(root);

/*
	node<double>* currentConnection;
	node<double>* smallest;
	node<double>* nextSmallest;
	for(int i = 0; i < weights.size(); i++){
		double tempWeights;
		if( i == 0){
			smallest = weights[0];
			nextSmallest = weights[1];
			if(weights[i] < smallest){
				smallest = weights[i];
			}
			else if(weights[i] < nextSmallest){
				nextSmallest = weights[i];
			}
			node* toAdd = node(smallest->get_weight() + nextSmallest->get_weight(), smallest, nextSmallest);	
			currentConnection = nextSmallest;			
		}
		else{
			smallest = currentConnection;
		}

		node* toAdd = node(smallest->get_weight() + nextSmallest->get_weight(), smallest, nextSmallest);
	}
*/
	// for(double i = 0; i < pathSize; i++){
	// 	cout << "Item " << i << " is "
	// 		 << path_vec[i].get_data()
	// 		 << " with a path of "  
	// 		 << path_vec[i].get_path() << endl;
	// }
	
	char letter;
	int count;
	string path;
	cout << "Insert letter: " << endl;
	cin >> letter; 
	for(int i = weights.size()-1; i > 0; i--){
		// cout << "Item " << i << " is " << weights[i].get_char() << " with a weight of " << weights[i].get_weight() << endl;
		if(weights[i].get_char() == letter){
			if(i==weights.size()){
				path = "1";
			}
			else{
				path.insert(0,"1"); 
			}
			cout << "Path nigga! " << path << endl;
			break;
		}
		else{
			path = path + "0";
		}
		count++;
		//totalWeight += weights[i].get_weight();
	}




	cout << "End!" << endl;	

	return 0;
}

void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight){
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
			totalWeight += weight;
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

void sortVector(vector<node<double> > &weights){
	int i, j;
	node<double> temp;
	for(i = weights.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(weights[j-1].get_weight() > weights[j].get_weight()){
				temp = weights[j-1];
				weights[j-1] = weights[j];
				weights[j] = temp;
			}
		}
	}
}

void printTree(node<double>* root){
	cout << root->get_weight() << endl;
	if(root == NULL){
		cout << "End" << endl;
	}
	else{
		if(root->isLeaf()){
			cout << "Leaf: " << root->get_char() 
				 << "\t weighs " << root->get_weight() << endl;
		}
		else{
			printTree(root->left_child());
			printTree(root->right_child());
		}
	}
}