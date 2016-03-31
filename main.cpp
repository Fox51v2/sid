#include<iostream>
#include<fstream>

#include"bTree.h"

using namespace std;

vector<bTree> readWeights(string fileName);

int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Give me a file name for the weights, ya dick: ";
	cin >> input; 
	vector<bTree> weights = readWeights(input);

	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is " <<
			 << weights[i].get_char() <<
			 << " with a weight of " << 
			 << weights[i].get_char() << endl;
	}
	cout << "\nAfter!" << endl;	
	return 0;
}

vector<bTree> readWeights(string fileName){
	//for line in file
	ifstream infile;
	char key;  			//first character is the data for node
	double weight;		//second string is weight of character 
	vector<bTree> trees;
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		if(temp != ""){
			key = temp[:1];
			weight = stod(temp[2:]);
		}
		bTree temp = bTree(key,weight);
		trees.push_back(temp);
	}
	return trees;
}
