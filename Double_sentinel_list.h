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
    Double_node *list_head = nullptr;
    Double_node *list_tail = nullptr;
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
//                                               Type    previous next
    Double_node *sentinel_tail = new Double_node(Type(), nullptr, nullptr);
    list_head = sentinel_head;
    list_tail = sentinel_tail;
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
list_size(0 )
{
    Double_sentinel_list *newList = new Double_sentinel_list();
    for (auto *it = list.begin(); it != list.end(); it = it->next()) {
        newList->push_back(it->value());
    }

    //TODO: Connect new list heads and tails and sizes

}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    //TODO: do this as well
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    delete list_size;
    //do this last
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    //TODO: maybe need to encapsulate in a try and catch
    //return list_head->next_node->next_node->next_node == list_tail ? true : false;
    return list_size == 0 ? true : false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    //TODO: encapsulte in try and catch
    return list_head->next_node->node_value;
    //     sentinel_head  first node  node value
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    //TODO: encapsulate in try and catch
    return list_tail->previous_node->node_value;
    //     sentinel_tail  last node      node value
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    return list_head->next();
    //is this returning an address?
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    return list_tail;
    //     sentinel tail
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    return list_tail->previous();
    //     sentinel tail last node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    return list_head;
    //     sentinel head
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    for (auto *it = this->begin(); it != this->end(); it = it->next()) {
        if (it->value() == obj) {
            return it;
        }
    }
    return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    int counter = 0;
    for (auto *it = this->begin(); it != this->end(); it = it->next()) {
        if (it->value() == obj) {
            counter++;
        }
    }
    return counter;
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
    Double_node *former_first_node = list_head->next_node;
    list_head->next_node = new Double_node(Type(), list_head, former_first_node);
    former_first_node->previous_node = list_head->next_node;

    list_head->next_node->node_value = obj;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node *former_last_node = list_tail->previous_node;
    former_last_node->next_node = new Double_node(Type(), list_tail, former_last_node);
    list_tail->previous_node = former_last_node->next_node;

    list_tail->previous_node->node_value = obj;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    //TODO: underflow exception
    //Ill have to create a temporary node so I don't have a memory leak
    Double_node *temp_first_node = list_head->next_node;
    list_head->next_node = list_head->next_node->next_node;
    temp_first_node->next_node->previous_node = list_head;

    list_size--;
    //delete first node
    delete temp_first_node;
    //verify that this deletes node and not just the pointer.
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    //TODO: underflow error
    Double_node *temp_last_node = list_tail->previous_node;

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
