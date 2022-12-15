#pragma once
#include "my_forward_list.h"

namespace my_std{
	//Showing other classes in my_std namespace
	template<typename T> class node;
	//*************************************************my_iterator class
	template <typename T>
	class my_iterator{
		public:
			//member aliases
			using difference_type = int;
			using value_type = T;
			using pointer = T*;
			using reference = T&;
			using iterator_category = std::forward_iterator_tag;
			//functions
			my_iterator();
			my_iterator(const my_iterator& Copy);
			my_iterator& operator=(const my_iterator& Copy);
			~my_iterator();
			//////////////////////swappable???????????????
			T& operator*();
			my_iterator& operator++();
			bool operator==(const my_iterator& Compare_to);
			bool operator!=(const my_iterator& Compare_to);
			//////////////////////my_iterator* operator->();
			my_std::my_iterator<T>& operator++(int);
		private:
			//values
			T temp{};
			node<T>* F_l_node{};
			static int c;
	};
}

//DEFINITIONS
//OK
template<typename T> int my_std::my_iterator<T>::c = 0;
//OK
template<typename T> my_std::my_iterator<T>::my_iterator() {
	F_l_node = new node<T>{};//-------------------------> USE Allocator_Traits HERE
	temp = F_l_node->val;
	//F_l_node = nullptr;
	std::cout<<"my_iterator`s default constructor -> allocated memory Nr_" << ++c << '\n';
}
//OK
template<typename T> my_std::my_iterator<T>::my_iterator(const my_iterator& Copy) {
	if (Copy.F_l_node) {
		F_l_node = new node<T>{}; //-------------------------> USE Allocator_Traits HERE
		*F_l_node = *Copy.F_l_node;
		temp = F_l_node->val;
		std::cout << "my_iterator`s copy constructor -> allocated memory Nr_" << ++c << '\n';
	}
	else {
		F_l_node = new node<T>{}; //-------------------------> USE Allocator_Traits HERE
		temp = F_l_node->val;
		std::cout << "my_iterator`s copy constructor -> Empty copy. Memory was allocated with default parameters. Mem Nr_ " << ++c << '\n';
	}
}
//OK
template<typename T> my_std::my_iterator<T>& my_std::my_iterator<T>::operator=(const my_iterator& Copy) {
	if (Copy.F_l_node) {
		if (F_l_node) {
			*F_l_node = *Copy.F_l_node;
			temp = F_l_node->val;
			std::cout << "my_iterator`s copy assignment operator -> working on previously allocated memory Nr_" << c << '\n';
			return *this;
		}
		else {
			F_l_node = new node<T>{};//-------------------------> USE Allocator_Traits HERE
			*F_l_node = *Copy.F_l_node;
			temp = F_l_node->val;
			std::cout << "my_iterator`s copy assignment operator -> allocated memory Nr_" << ++c << '\n';
			return *this;			
		}
	}
	else {
		if (F_l_node) {
			delete F_l_node;//-------------------------> USE Allocator_Traits HERE
			F_l_node = nullptr;
			std::cout << "my_iterator`s copy assignment deleting current pointer Nr_" << --c << '\n';
			return *this;
		}
		else {
			std::cout << "my_iterator`s copy assignment operator -> memory wasn`t allocated. Curr state = nullptr. Mem Nr_" << c << '\n';
		}
	}
}
//OK
template<typename T> my_std::my_iterator<T>::~my_iterator() {
	if (F_l_node) {
		delete F_l_node;//-------------------------> USE Allocator_Traits HERE
		std::cout << "my_iterator`s destructor deleting it`s pointer Nr_" << c-- << '\n';
	}
	else {
		std::cout << "my_iterator`s destructor: memory wasn`t allocated " << c << '\n';
		F_l_node = nullptr;
	}
}
//OK
template<typename T> T& my_std::my_iterator<T>::operator*() {
	if (F_l_node)
		return temp;
	else {
		std::cout << "Operator* -> empty Iterator -> no memory allocated. No value! \n";
		T a{};
		return a;
	}
}
//OK
template<typename T> my_std::my_iterator<T>& my_std::my_iterator<T>::operator++() {
	if (F_l_node){
		if (F_l_node->Next) {
			*F_l_node = *F_l_node->Next;
			temp = F_l_node->val;
			return *this;
		}
		else {
			delete F_l_node;//-------------------------> USE Allocator_Traits HERE
			F_l_node = nullptr;
			std::cout << "my_iterator`s operator++() deleting current pointer Nr_" << --c << '\n';
			return *this;
		}
	}
	else std::cout << "Operator++ -> empty Iterator -> no memory allocated. No value! " << c << '\n';
}
//OK
template<typename T> bool my_std::my_iterator<T>::operator==(const my_iterator& Compare_to) {
	if (Compare_to.F_l_node && F_l_node) {
		temp = F_l_node->val;
		return F_l_node->val == Compare_to.F_l_node->val;
	}
	else {
		return  0;
	}
}
//OK
template<typename T> bool my_std::my_iterator<T>::operator!=(const my_iterator& Compare_to) {
	return !(*this == Compare_to);
}
//OK
template<typename T> my_std::my_iterator<T>& my_std::my_iterator<T>::operator++(int) {
	if (F_l_node) {
		temp = F_l_node->val;
		if (F_l_node->Next) {
			*F_l_node = *F_l_node->Next;
			return *this;
		}
		else {
			delete F_l_node;//-------------------------> USE Allocator_Traits HERE
			F_l_node = nullptr;
			std::cout << "my_iterator`s operator++(int) deleting current pointer Nr_" << --c << '\n';
			return *this;
		}
	}
	else std::cout << "Operator++ -> empty Iterator -> no memory allocated. No value! " << c << '\n';
}
/*
template<typename T> my_std::my_iterator<T>* my_std::my_iterator<T>::operator->() {
	return this;
}*/