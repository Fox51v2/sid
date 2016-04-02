#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include"Node.cpp"
#include"Path.cpp"
#include<string>
using namespace std;

void readWeights(string fileName, vector<Node> *weights);
void readPath(string fileName, vector<Path> *path_vec);
int pathSize;
double totalWeight = 0;
int main(){
	cout << "Before!" << endl;
	string input;
	cout << "Enter the weights file name: ";
	cin >> input; 
	vector<Node> weights;
	vector<Path> path_vec;
	readWeights(input,&weights);
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);

	for(int i = 0; i < weights.size(); i++){

		cout << "Item " << i << " is " << weights[i].get_char()
			 << " with a weight of "  
			 << weights[i].get_weight() << endl;



		totalWeight = totalWeight + weights[i].get_weight();
		//cout << "totalWeight: " << totalWeight << endl;

	}
	cout << "totalWeight: " << totalWeight << endl;


	// for(int i = 0; i < pathSize; i++){
	// 	cout << "Item " << i << " is "
	// 		 << path_vec[i].get_data()
	// 		 << " with a path of "  
	// 		 << path_vec[i].get_path() << endl;
	// }
	cout << "\nAfter!" << endl;	
	return 0;
}

void readWeights(string fileName, vector<Node> *weights){
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
		if(temp != " "){
			key = temp[0];
			//cout << "Key: " << key << endl;
			weight = atof(temp.substr(2,temp.size()-1).c_str());
			//cout << "weight: " << weight<<endl;
			Node tempNode = Node(weight, key);
			weights->push_back(tempNode);
		}
	}

}
void readPath(string fileName, vector<Path> *path_vec){
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

