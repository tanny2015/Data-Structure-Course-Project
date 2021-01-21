//
// Created by tanny on 6/16/2020.
//

#include <iostream>
//#include <cstddef>
#include <stdexcept>
using std::endl;
using std::cout;
using std::runtime_error;

template <class T>
class Node{
public:
    T data;
    Node* next;
    Node* previous;
    //Constructors
    Node(T val):data(val), previous(nullptr), next(nullptr){;};
    Node(T val,Node* previous,Node* next): data(val),previous(previous),next(next){;};
};

template <class T>
class Deque{
public:

/* Default Constructor
 * POST: Creates an empty Deque
 * */
Deque();

/* Copy Constructor
 * PARAM: The deque to be deeply copied into
 * POST: Creates a deep copy of its constant Deque reference parameter
 * */
Deque(const Deque &dq);

/* Destructor
 * POST: Deallocate dynamic memory allocated by the Deque
 * */
~Deque();

/* Operator= Overload
 * PARAM: The deque to be deeply copied into
 * POST: Deeply copies its constant Deque reference parameter into the calling object and returns a
 * reference to the calling object after deallocating any dynamic memory associated with the original
 * contents of the calling object; if the calling object is the same as the parameter the operator
 * should not copy it
 * */
Deque & operator=(const Deque &dq);

/* InsertFront
 * PARAM:The value to be inserted
 * POST: Inserts its template parameter at the front of the Deque
 * */
void insertFront(T value);

/* InsertBack
 * PARAM:The value to be inserted
 * POST: Inserts its template parameter at the back of the Deque
 * */
void insertBack(T value);

/* RemoveFront
 * POST: Removes and returns the value at the front of the Deque; if the Deque is empty throws a runtime_error
 * */
T removeFront();

/* RemoveBack
 * POST: Removes and returns the value at the back of the Deque; if theDeque is empty throws a runtime_error
 * */
T removeBack();

/* PeekFront
 * POST: Returns the value at the front of the Deque without removing it; if the Deque is empty
 * throws a runtime_error
 * */
T peekFront() const;

/* PeekBack
 * POST: Returns the value at the back of the Deque without removing it; if the Deque is empty
 * throws a runtime_error
 * */
T peekBack() const;

/* Empty
 * POST: Returns true if the Deque is empty, false otherwise
 * */
bool empty() const;

/* Size
 * POST: Returns the number of items stored in the Deque, as an int
 * */
int size() const;

private:
    Node<T> * front;
    Node<T> * back ;
    void copyDeque(const Deque & dq);
    void deleteDeque();
};

/* Default Constructor
 * POST: Creates an empty Deque
 * */
template <class T>
Deque<T>::Deque(){
    front = nullptr;
    back = nullptr;
}

/* Copy Constructor
 * PARAM: The deque to be deeply copied into
 * POST: Creates a deep copy of its constant Deque reference parameter
 * */
template <class T>
Deque<T>::Deque(const Deque &dq){
    copyDeque(dq);
}

/* Destructor
 * POST: Deallocate dynamic memory allocated by the Deque
 * */
template <class T>
Deque<T>::~Deque(){
    deleteDeque();
}

/* Operator= Overload
 * PARAM: The deque to be deeply copied into
 * POST: Deeply copies its constant Deque reference parameter into the calling object and returns a
 * reference to the calling object after deallocating any dynamic memory associated with the original
 * contents of the calling object; if the calling object is the same as the parameter the operator
 * should not copy it
 * */
template <class T>
Deque<T> & Deque<T>::operator=(const Deque &dq){
    if(this != &dq){
        deleteDeque();
        copyDeque(dq);
    }
    return *this;
}

/* InsertFront
 * PARAM:The value to be inserted
 * POST: Inserts its template parameter at the front of the Deque
 * */
template <class T>
void Deque<T>::insertFront(T value){
    Node<T> *nd = new Node<T>(value, nullptr, front);
    if (front== nullptr){
        front = nd;
        back = nd;
    } else{
        front->previous = nd;
        front = nd;
    }
}

/* InsertBack
 * PARAM:The value to be inserted
 * POST: Inserts its template parameter at the back of the Deque
 * */
template <class T>
void Deque<T>::insertBack(T value){
    Node<T> *nd = new Node<T>(value, back, nullptr);
    if (back == nullptr){
        front = nd;
        back = nd;
    } else {
        back->next = nd;
        back = nd;
    }
}

/* RemoveFront
 * POST: Removes and returns the value at the front of the Deque; if the Deque is empty throws a runtime_error
 * */
template <class T>
T Deque<T>::removeFront(){
    if (front == nullptr){
        throw runtime_error("Deque Empty -removeFront");
    } else{
        Node<T> * temp = front;
        T data_to_delete = temp -> data;
        front = front->next;

        //empty after remove the last node
        if (front == nullptr){
            back = nullptr;
        } else{
            front->previous = nullptr;
        }
        delete temp;
        return data_to_delete;
    }
}

/* RemoveBack
 * POST: Removes and returns the value at the back of the Deque; if theDeque is empty throws a runtime_error
 * */
template <class T>
T Deque<T>::removeBack(){
    if (back == nullptr){
        throw runtime_error("Deque Empty -removeBack");
    }else{
        Node<T> * temp = back;
        T data_to_delete = temp -> data;
        back = back->previous;

        //empty after delete the last node
        if(back == nullptr){
            front = nullptr;
        } else{
            back->next = nullptr;
        }
        delete temp;
        return data_to_delete;
    }
}

/* PeekFront
 * POST: Returns the value at the front of the Deque without removing it; if the Deque is empty
 * throws a runtime_error
 * */
template <class T>
T Deque<T>::peekFront() const{
    if (front == nullptr){
        throw runtime_error("Deque Empty -peekFront");
    } else{
        return front->data;
    }
}

/* PeekBack
 * POST: Returns the value at the back of the Deque without removing it; if the Deque is empty
 * throws a runtime_error
 * */
template <class T>
T Deque<T>::peekBack() const{
    if (back == nullptr){
        throw runtime_error("Deque Empty -peekBack");
    } else{
        return back->data;
    }
}

/* Empty
 * POST: Returns true if the Deque is empty, false otherwise
 * */
template <class T>
bool Deque<T>::empty() const{
    return front == nullptr;
}

/* Size
 * POST: Returns the number of items stored in the Deque, as an int
 * */
template <class T>
int Deque<T>::size() const{
    int i = 0;
    Node<T> *it = front;
    while (it!= nullptr){
        ++i;
        it=it->next;
    }
    return i;
}

template <class T>
void Deque<T>::copyDeque(const Deque & dq){
    front = nullptr;
    Node<T> *origin = dq.front;
    if (origin != nullptr) {
        front = new Node<T>(origin->data);
        front->previous = nullptr;
        origin = origin->next;
        Node<T> *copy = front;
        while (origin != nullptr) {
            Node<T> * nd = new Node<T>(origin->data);
            copy->next = nd;
            nd->previous = copy;
            copy = copy -> next;
            origin = origin -> next;
        }
        back = copy;
    }
}


template <class T>
void Deque<T>::deleteDeque(){
    Node<T> * it = front;
    while (front != nullptr){
        front = front->next;
        delete it;
        it = front;
    }
    back = nullptr;
}
