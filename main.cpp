#include<iostream>
#include<fstream>
#include<vector>
#include"Node.cpp"
#include<string>
using namespace std;

void readWeights(string fileName, vector<Node> &weights);

int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Give me a file name for the weights, ya dick: ";
	cin >> input; 
	vector<Node> weights;
	readWeights(input,weights);

	for(int i = 0; i < weights.size(); i++){
		cout << "Item " << i << " is "
			 << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_char() << endl;
	}
	cout << "\nAfter!" << endl;	
	return 0;
}

void readWeights(string fileName, vector<Node> &weights){
	//for line in file
	ifstream infile;
	char key;  			//first character is the data for node
	double weight;		//second string is weight of character 
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		cout << "This line: " << temp << endl;
		if(temp != ""){
			key = temp[0];
			cout << "Key: " << key << endl;
			weight = atof(temp.substr(2,temp.size()-1).c_str());
			Node tempNode = Node(key,weight);
			weights.push_back(tempNode);
		}
	}
}
