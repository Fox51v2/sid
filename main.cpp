#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include"charFreq.h"
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>


using namespace std;


string encode(node<double>* root, string c);
void Decode(node<double>* root, string encoded);
void readWeightsFile(string fileName, vector<node<double> > &weights, int sizeOfTree);
void readPath(string fileName, vector<Path> *path_vec);
void sortVector(vector<node<double> > &weights);
void sortNodeVector(vector<node<double>* > &nodes);
void printTree(node<double>* root);
void printPath(node<double>* root,string letter);
void printCodes(struct node<double>* root, int arr[], int top);
int isLeaf(struct node<double> * root);
string getPath(int arr[], int n);
node<double>* buildHuffmanTree(vector<node<double>* > &nodeVector);
bool charAlreadyEncountered(vector<node<double>* > nodes, string s);
int nodeIndexOf(vector<node<double>* > nodes, string c);
node<double>* treeFromTextFile(string filename, vector<node<double>* > &nodes);
void treeSize(node<double>* root, int &size);

int main(){
	


	string weightsFile;
	cout << "Enter the weights file name: ";
	cin >> weightsFile; 
	node<double>* first;
	vector<Path> path_vec;
	vector<node<double> > weights;
	int sizeOfTree = 0;
	readWeightsFile(weightsFile, weights, sizeOfTree);
	//cout << "Weights created" << endl;
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);
		
	sortVector(weights);
 	
 	vector<node<double>* > nodes;
	for(int i = 0; i < weights.size(); i++){
		nodes.push_back(new node<double>(weights[i].get_weight(),weights[i].get_char(),NULL,NULL));
	}
	cout << "Weights size: " << weights.size() << endl;
	node<double>* newRoot = buildHuffmanTree(nodes);
	int sizeOfNewRoot = 0;
	treeSize(newRoot, sizeOfNewRoot);
	cout << "sizeOfNewRoot: " << sizeOfNewRoot << endl;
	printTree(newRoot);
	int arr[sizeOfNewRoot], top = 0;
	printCodes(newRoot, arr, top);
	//cout << "Populated nodes vector" << endl;
	

	//node<double>* root = buildHuffmanTree(nodes,totalWeight);
	//printTree(root);
	/*
	vector<node<double>* > tester;
	node<double>* test = treeFromTextFile("frequency.txt", tester);
	printTree(test);
	int sizeOfTest = 0;
	treeSize(test,sizeOfTest);
	int testArr[sizeOfTest];
	printCodes(test, testArr, top);
*/
/*
	Decode(root,"1111");
	Decode(root,encode(root,"h"));
	cout << "Past Decoding" << endl;
	// Diego is sending the path to this function
*/
	//string path = encode(test,"a");
	string path = encode(newRoot," ");

	FILE * dat = fopen ("data.dat", "wb");
	fwrite (&path, sizeof(path), 1, dat);
	fclose(dat);

	dat = fopen("data.dat", "rb");
	fread (&path, sizeof(path), 1, dat);
	cout << "this is the path after decoding "<<path << endl;
	/*string temp;
	while (!dat.eof()){
		getline(dat, temp);
		cout <<temp<<endl;
	}*/	
	fclose(dat);

//	printCodes(root, arr, top1);

	cout << "End!" << endl;	
	return 0;
}

int isLeaf(struct node<double> * root){
    return !(root->left_child()) && !(root->right_child()) ;
}

void printCodes(struct node<double>* root, int arr[], int top){
    // Assign 0 to left edge and recur
    if (root->left_child())
    {
        arr[top] = 0;
        printCodes(root->left_child(), arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right_child())
    {
        arr[top] = 1;
        printCodes(root->right_child(), arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        cout << root->get_char() <<endl;
        string temp;
        temp = getPath(arr, top);
    }
    //return temp;
}

string getPath(int arr[], int n)
{
    int i;
    string stringPath = "";
    string text;
    for (i = 0; i < n; ++i){
    	int number = arr[i];
    	string Result;
    	ostringstream convert;
    	convert << number;
    	text = convert.str();
    	stringPath += text;
    }
    cout << stringPath << endl;
    return stringPath;
}

string encode(node<double>* root, string c){
	string path = "";
	node<double>* lastRoot = root;
	//cout << "Searching for " << c << endl;
	while(lastRoot->get_char().length() != 1){				//while looking through the tree
		if(lastRoot->right_child()->get_char().find(c) != string::npos){		//if the right child contains the letter
			path += "1";
			//cout << "Contents: " << lastRoot->get_char() << endl;											
			if(lastRoot->right_child()){						
				lastRoot = lastRoot->right_child();
			}
		}
		else if(lastRoot->left_child()->get_char().find(c) != string::npos){	//if the left child contains the letter
			path += "0";
			//cout << "Contents: " << lastRoot->get_char() << endl;
			if(lastRoot->left_child()){
				lastRoot = lastRoot->left_child();
			}
		}
	}
	return path;	
}

void readWeightsFile(string fileName, vector<node<double> > &weights, int size){
	//for line in file
	ifstream infile;
	string key;  			//first character is the data for node
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
			size++;
		}
	}
}

void readPath(string fileName, vector<Path> *path_vec, int pathSize){
	//for line in file
	ifstream infile;
	//sting key;		//first character is the data for node
	double 	pathBinary = 0;		//second string is path of character 
	infile.open(fileName.c_str());
	while(infile.get() != infile.eof()){
		string temp;			
		getline(infile, temp);
		// cout << "This line: " << temp << endl;
		if(temp != ""){
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

void sortNodeVector(vector<node<double>* > &nodes){
	int i, j;
	node<double>* temp;
	for(i = nodes.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(nodes[j-1]->get_weight() > nodes[j]->get_weight()){
				temp = nodes[j-1];
				nodes[j-1] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}

void printTree(node<double>* root){
	// cout << root->get_weight() << endl;
	if(root){
		cout << "Root contents: "
			 << root->get_char() << "-"
			 << root->get_weight() << endl;
		if(root->left_child()){ 
		//	cout << "Left" << endl; 
			printTree(root->left_child());
		}
		if(root->right_child()){
		//	cout << "Right" << endl;
			printTree(root->right_child());
		}
		//cout << root->get_char() << endl;
	}
}

void Decode(node<double>* root, string encoded){
	 node<double>* ptrRoot = root;
	 string finalCharacter; 
	 for (int i = 0; i < encoded.size(); i ++){
	 	if (encoded[i] == '0'){
	 		if(ptrRoot->left_child())
	 			ptrRoot = ptrRoot->left_child();
	 	}
 		else if(encoded[i] == '1'){
 			if(ptrRoot->right_child())
 				ptrRoot = ptrRoot->right_child(); 	
	 	}
	 	//cout << ptrRoot->get_char() << " ptrRoot contents <<" << endl;
	 }
	 finalCharacter = ptrRoot->get_char();
	 //cout << "The decoded binary code is: " << finalCharacter << endl;
}

//build a tree, given a vector of node pointers
node<double>* buildHuffmanTree(vector<node<double>* > &nodeVector){
	node<double>* newNode;
	while(nodeVector.size() > 1){
		sortNodeVector(nodeVector);					//sort the vector
		node<double>* smallest = nodeVector[0]; 		//the last item is smallest
		node<double>* nextSmallest = nodeVector[1];	//the second to last item is next smallest
		newNode = new node<double>(smallest->get_weight()+nextSmallest->get_weight(),
					smallest->get_char()+nextSmallest->get_char(), smallest,nextSmallest);	//make a new node
		nodeVector.erase(nodeVector.begin());						//we used smallest already
		nodeVector.erase(nodeVector.begin());						//we used nextSmallest, too
		nodeVector.push_back(newNode);				//add new node into the vector
		//cout << "Added node with weight " << nodes.back()->get_weight() << endl;
	}
	return nodeVector[0];
}

//determines if character is already in vector
bool charAlreadyEncountered(vector<node<double>* > nodes, string s){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->get_char().compare(s) == 0){
			return true;
		}
	}
	return false;
}

//returns index of character in vector
int nodeIndexOf(vector<node<double>* > nodes, string c){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->get_char().compare(c) == 0){
			return i;
		}
	}
	return -1;
}

void treeSize(node<double>* root, int &size){
	if(root->isLeaf()){
		size++;
	}
	else{
		treeSize(root->left_child(), size);
		treeSize(root->right_child(), size);
	}
}

node<double>* treeFromTextFile(string filename, vector<node<double>* > &nodes){
	ifstream infile;
	infile.open(filename.c_str());
	char nextChar;
	while(infile.get(nextChar) && nextChar != infile.eof()){
		string thisChar;
		stringstream ss;
		ss >> noskipws;
		ss << nextChar;
		ss >> thisChar;
		if(!charAlreadyEncountered(nodes, thisChar)){
			node<double>* temp = new node<double>(1,thisChar);
			nodes.push_back(temp);
		}
		else if(charAlreadyEncountered){
			nodes[nodeIndexOf(nodes, thisChar)]->inc_Weight();
		}
	}
	return buildHuffmanTree(nodes);
}
