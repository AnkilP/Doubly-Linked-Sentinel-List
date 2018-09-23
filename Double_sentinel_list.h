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

    //My own private members
    void pop(Double_node *it);

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

list_size(0 )
{
    list_head = new Double_node(Type(), nullptr, nullptr);
//                              Type    previous next
    list_tail = new Double_node(Type(), nullptr, nullptr);
    list_head->next_node = sentinel_tail;
    list_tail->previous_node = sentinel_head;
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
        list_head(nullptr),
        list_tail(nullptr),
        list_size(0 )
{
    Double_sentinel_list *newList = new Double_sentinel_list();
    for (auto *it = list.begin(); it != list.end(); it = it->next()) {
        newList->push_back(it->value());
    }
    swap(newList);
    delete newList;
}

/*
 *The move constructor must create a new doubly linked list with all the nodes found within the linked
list passed as an argument list with the values stored in the same order. It is assumed that the
destructor will immediately be called on the argument linked list as soon as this constructor finishes,
so all the nodes in the argument linked list can be used in this newly created linked list. The
argument linked list should be updated to one that is empty. (This is most easily done by initializing
this linked list as an empty linked list and then calling swap.) (O(1))
 */

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
//list_head( nullptr ),
//list_tail( nullptr ),
list_size(0 )
{
//	list_head = list.list_head;
//	list_tail = list.list_tail;
    list_head = new Double_node(Type(), nullptr, nullptr);
//                              Type    previous  next
    list_tail = new Double_node(Type(), nullptr, nullptr);
    list_head->next_node = sentinel_tail;
    list_tail->previous_node = sentinel_head;

    swap(list);

//	list_size = list.list_size;
}

/*
 * The destructor must delete each of the nodes in the list including the sentinels. (O(n))
 */

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    delete list_size;
    //unsafe use of nullptr?
    for (auto *it = begin()->next(); it != nullptr; it = it->next()) {
        delete it->previous_node;
    }

    //do this last
    delete list_head;
    delete list_tail;
}

/*
 * Returns the number of items in the list. (O(1))
 */

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size;
}

/*
 * Returns true if the list is empty, false otherwise. (O(1))
 */

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    return list_size == 0 ? true : false;
}

/*
 * Retrieves the object stored in the node pointed to by the next pointer of the head sentinel.
This function throws a underflow if the list is empty. (O(1))
 */

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    if (empty() == true) {
        throw underflow;
    }
    return list_head->next_node->node_value;
    //     sentinel_head  first node  node value
}

/*
 * Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel.
This function throws a underflow if the list is empty. (O(1))
 */

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if (empty() == true) {
        throw underflow;
    }
    return list_tail->previous_node->node_value;
    //     sentinel_tail  last node      node value

}

/*
 * Returns the address stored by the next pointer of the head sentinel node. (O(1))
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    return list_head->next();
    //is this returning an address?
}

/*
 * Returns the address of the tail sentinel node. (O(1))
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    return list_tail;
    //     sentinel tail
}

/*
 * Returns the address stored by the previous pointer of the tail sentinel node. (O(1))
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    return list_tail->previous();
    //     sentinel tail last node
}

/*
 * Returns the address of the head sentinel node. (O(1))
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    return list_head;
    //     sentinel head
}

/*
 * Returns the address of the first node in the linked list storing a value equal to the argument; if
none is found, return end(). (O(n))
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find(Type const &obj ) const {
    for (auto *it = this->begin(); it != this->end(); it = it->next()) {
        if (it->value() == obj) {
            return it;
            //TODO: check for memory leaks
        }
    }
    return end();
}

/*
 * Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
 */

template <typename Type>
int Double_sentinel_list<Type>::count(Type const &obj ) const {
    int counter = 0;
    for (auto *it = this->begin(); it != this->end(); it = it->next()) {
        if (it->value() == obj) {
            counter++;
        }
    }
    return counter;
}

/*
 * The swap function swaps all the member variables of this linked list with those of the
argument list. (O(1))
 */

template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list ) {
    // This is done for you
    std::swap(list_head, list.list_head );
    std::swap(list_tail, list.list_tail );
    std::swap(list_size, list.list_size );
}

/*
 * The assignment operator makes a copy of the argument (the right-hand side of the
assignment) and then swaps the member variables of this node doubly linked sentinel list
those of the copy. (O(nlhs + nrhs))
 */

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

/*
 * The move operator moves the nodes in the argument (the right-hand side of the assignment)
linked list to this linked list, changing the argument linked list into an empty list. (O(1))
 */

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

/*
 * Creates a new Double_node<Type> storing the argument new_value, the next pointer
of which is set to the next pointer of the sentinel and the previous pointer is set to point to the
sentinel. The next pointer of the sentinel and the previous pointer of what was the first node
are set to this new node. (O(1))
 */

template <typename Type>
void Double_sentinel_list<Type>::push_front(Type const &obj ) {
    Double_node *former_first_node = list_head->next_node;
    list_head->next_node = new Double_node(Type(), list_head, former_first_node);
    former_first_node->previous_node = list_head->next_node;

    list_head->next_node->node_value = obj;
    list_size++;
}

/*
 * Similar to push_front, this places a new node at the back of the list storing the
argument new_value. (O(1))
 */

template <typename Type>
void Double_sentinel_list<Type>::push_back(Type const &obj ) {
    Double_node *former_last_node = list_tail->previous_node;
    former_last_node->next_node = new Double_node(Type(), list_tail, former_last_node);
    list_tail->previous_node = former_last_node->next_node;

    list_tail->previous_node->node_value = obj;
    list_size++;
}

/*
 * Delete the first non-sentinel node at the front of the linked list and update the previous and
next pointers of any other node (including possibly the sentinels) within the list as necessary.
Throw an underflow exception if the list is empty. (O(1))
 */

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
    //TODO: verify that this deletes node and not just the pointer.
    //Apparently this should work
}

/*
 * Similar to pop_front, delete the last non-sentinel node in the list. This function throws
an underflow if the list is empty. (O(1))
 */

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    //TODO: underflow error
    Double_node *temp_last_node = list_tail->previous_node;
    list_tail->previous_node = list_tail->previous_node->previous_node;
    temp_last_node->previous_node->next_node = list_tail;

    list_size--;
    delete temp_last_node;
    //TODO: verify that this deletes node and not just the pointer
    //this should delete the pointer
}

/*
 * Delete all the nodes in the linked list that have a value equal to the
argument value (use == to test for equality with the retrieved element). Update the
previous and next pointers of any other node (including possibly the sentinels) within the list.
Return the number of nodes that were deleted. (O(n))
 */

template <typename Type>
int Double_sentinel_list<Type>::erase(Type const &obj ) {
    int counter = 0;
    for (Double_node *it = begin(); it != end(); it = it->next()) {
        if (it->value() == obj) {
            pop(it);
            counter++;
            list_size--;
        }
    }
    return counter;
}

/*
 * This constructor sets up the node value, previous node and next node.
 */

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
        Type const &nv,
        typename Double_sentinel_list<Type>::Double_node *pn,
        typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value(Type() ), // This assigns 'node_value' the default value of Type
previous_node(nullptr ),
next_node(nullptr )
{
    node_value = nv;
    previous_node = pn;
    next_node = nn;
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
    return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
    return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
    return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

template<typename Type>
void Double_sentinel_list<Type>::pop(Double_node *it) {
    //TODO: exception handling
    Double_node *temp_previous = it->previous_node;
    //
    Double_node *temp_next = it->next_node;
    temp_previous->next_node = temp_next;
    temp_next->previous_node = temp_previous;
    Double_node *delete_it = it;
    it = temp_previous;
    delete delete_it;
}

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
