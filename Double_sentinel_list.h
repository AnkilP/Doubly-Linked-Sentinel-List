/*****************************************
 * UW User ID:  a293pate
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

/////
				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

/////
				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

/*
 * The constructor creates two instances of a Double_node<Type> (called the sentinels). The head
and tail pointers are set to point to one of the sentinels, each. The values stored in these nodes is
not important, you can use the default value or whatever values you want. The previous and next
pointers of the head sentinel should be nullptr and the address of the tail sentinel, respectively.
The previous and next pointers of the tail sentinel should be the address of the head sentinel
and nullptr, respectively. The node count is set to 0. (O(1))
 */

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head(nullptr ),
list_tail(nullptr ),
list_size(0 )
{
    Double_node *sentinel_head = new Double_node(Type(), nullptr, nullptr);
    Double_node *sentinel_tail = new Double_node(Type(), nullptr, nullptr);
    list_head->next_node = sentinel_head;
    list_tail->previous_node = sentinel_tail;
    sentinel_head->next_node = sentinel_tail;
    sentinel_tail->previous_node = sentinel_head;
}

/*
 * The copy constructor must create a new doubly linked list with a copy of all of the nodes within the
linked list pass as the argument list with the values stored in the same order. The linked list
passed as an argument may not be changed. Once a copy is made, any change to the original linked
list must not affect the copy. (O(n))
 */

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head(nullptr ),
list_tail(nullptr ),
list_size(0 )
{
    Double_node *sentinel_head = new Double_node(Type(), nullptr, nullptr);
    Double_node *sentinel_tail = new Double_node(Type(), nullptr, nullptr);
    list_head->next_node = sentinel_head;
    list_tail->previous_node = sentinel_tail;
    for (int i = 0; i < list.size(); ++i) {
        //TODO: go through each node in new list
        list_size++;
    }

}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Enter your implementation here
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    //TODO: maybe need to encapsulate in a try and catch
    return list_head->next_node->next_node->next_node == list_tail ? true : false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    //TODO: encapsulte in try and catch
    return list_head->next_node->next_node->node_value;
    //     list head   sentinel    first node  node value
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //TODO: encapsulate in try and catch
    return list_tail->previous_node->previous_node->node_value;
    //     list tail    sentinel tail    last node        node value
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    return list_head->next_node.next();
    //is this returning an address?
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    return list_tail->previous_node;
    //     list tail  sentinel tail
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    return list_tail->previous_node.previous();
    //     list tail  sentinel tail last node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    return list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    for (auto *it = this->begin(); it != this->end(); it = it->next()) {
        if (it->node_value == obj) {
            return it;
        }
    }
    return std::cout << "This value doesn't exist" << std::endl;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	return 0;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Enter your implementation here
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	return 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return nullptr;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
