#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class Node{
private:
	char data;
	double weight;
	Node *left;
	Node *right;
	

public:
	Node (){
		left = NULL;
		right = NULL;
	}
	Node(double w, Node * L = NULL, Node * R = NULL){
		weight = w;
		left = L;
		right = R; 
	}

	Node (double w, char d, Node * L = NULL, Node * R = NULL){
		weight = w;
		left = L;
		right = R;
		data = d;
	}
	char get_char(){
		return data;
	}
	double get_weight(){
		return weight;
	}
	void set_weight(double w){
		weight = w;
	}
	Node * left_child(){
		return left;
	}
	Node * right_child(){
		return right;
	}
	void set_left(Node *L){
		left = L;
	}
	void set_right(Node *R){
		right = R;
	}
	bool isLeaf(){
		return ((left == NULL)&& (right == NULL));
	}

};