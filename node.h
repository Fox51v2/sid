#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

template<typename T> class node{
	private:
		char data;
		T weight;
		node* left;
		node* right;
	public:
		node();
		node(T, node* L=NULL, node* R=NULL);
		node(T w, char d, node* L=NULL, node* R=NULL);
		char get_char();
		T get_weight();
		void set_weight(T w);
		node* left_child();
		node* right_child();
		void set_left(node* L);
		void set_right(node* R);
		bool isLeaf();
};

template <typename T>
node<T>::node(){
	left,right = NULL;

}
template<typename T>
node<T>::node (T w,node* L,node* R){
	weight = w; left = L; right = R; 
}

template<typename T>
node<T>::node(T w, char d, node* L, node* R){
	weight = w;	left = L; right = R; data = d;
}

template<typename T> 
char node<T>::get_char(){
	return data;
}

template<typename T>
T node<T>::get_weight(){
	return weight;
}

template<typename T> 
void node<T>::set_weight(T w){
	weight = w;
}

template<typename T> 
node<T>* node<T>::left_child(){
	return left;
}

template<typename T> class 
node<T>* node<T>::right_child(){
	return right;
}

template<typename T> 
void node<T>::set_left(node *L){
	left = L;
}

template<typename T> 
void node<T>::set_right(node *R){
	right = R;
}

template<typename T> 
bool node<T>::isLeaf(){
	return ((left == NULL)&& (right == NULL));
}
