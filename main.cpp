#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>


using namespace std;


string encode(node<double>* root, string c);
void Decode(node<double>* root, string encoded);
void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight);
void readPath(string fileName, vector<Path> *path_vec);
void sortVector(vector<node<double> > &weights);
void sortNodeVector(vector<node<double>* > &nodes);
void printTree(node<double>* root);
void printPath(node<double>* root,string letter);
void printCodes(struct node <double>* root, int arr[], int top);
int isLeaf(struct node<double> * root);
string getPath(int arr[], int n);
int NumChar= 0 ;




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
	//cout << "Weights created" << endl;
	int sizeOfTree = weights.size();
	//cout << "Enter the path file name: ";
	//cin >> input;
	//readPath(input, &path_vec);
		
	sortVector(weights);
 	
 	vector<node<double>* > nodes;
	for(int i = 0; i < weights.size(); i++){
		nodes.push_back(new node<double>(weights[i].get_weight(),weights[i].get_char(),NULL,NULL));
	}
	//cout << "Populated nodes vector" << endl;
	


	node<double>* newNode;
	while(nodes[0]->get_weight() != totalWeight){
		sortNodeVector(nodes);					//sort the vector
		node<double>* smallest = nodes[0]; 		//the last item is smallest
		node<double>* nextSmallest = nodes[1];	//the second to last item is next smallest
		/*
		cout << "Building new node..." << endl;
		cout << "From characters: " 
				<< smallest->get_char() << " and "
				<< nextSmallest->get_char() << endl;
		cout << "From weights: "
				<< smallest->get_weight() << " and "
				<< nextSmallest->get_weight() << endl;
		*/
		newNode = new node<double>(smallest->get_weight()+nextSmallest->get_weight(),
					smallest->get_char()+nextSmallest->get_char(), smallest,nextSmallest);	//make a new node
		nodes.erase(nodes.begin());						//we used smallest already
		nodes.erase(nodes.begin());						//we used nextSmallest, too
		nodes.push_back(newNode);				//add new node into the vector
		
		//cout << "Added node with weight " << nodes.back()->get_weight() << endl;
	}
	node<double>* root = nodes[0];
	printTree(root);

	Decode(root,"1111");
	Decode(root,encode(root,"h"));
	cout << "Past Decoding" << endl;

	// Diego is sending the path to this function
//printPath(root,letter);ZZ


	// this is the working for writing and reading the bit into the file 
	string path = encode(root, "a");
	cout << "this is the path to a: " << path <<endl;
	FILE * dat = fopen ("data.dat", "wb");
	fwrite (&path, sizeof(unsigned char), 1, dat);
	fclose(dat);

	dat = fopen("data.dat", "rb");
	fread (&path, sizeof(unsigned char), 1, dat);
	cout << "this is the path after decoding "<<path << endl;
	/*string temp;
	while (!dat.eof()){
		getline(dat, temp);
		cout <<temp<<endl;
	}*/	
	fclose(dat);



//	int arr[NumChar], top1 = 0;
//	printCodes(root, arr, top1);

	cout << "End!" << endl;	
	return 0;
}
int isLeaf(struct node<double> * root)
{
    return !(root->left_child()) && !(root->right_child()) ;
}
void printCodes(struct node<double>* root, int arr[], int top)
{
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
        //printf("%d", arr[i]);
    //printf("\n");
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

void readWeights(string fileName, vector<node<double> > &weights, double &totalWeight){
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
			totalWeight += weight;
			//cout << "weight: " << weight<<endl;
			node<double> tempnode = node<double>(weight, key);
		//	cout << "About to push" << endl;
			weights.push_back(tempnode);
			NumChar ++;
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
	if(root != NULL){
		/*
		cout << "Root contents: "
			 << root->get_char() << ""
			 << root->get_weight() << endl;
		*/
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
