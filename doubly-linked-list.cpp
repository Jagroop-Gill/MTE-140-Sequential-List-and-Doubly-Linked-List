#include "doubly-linked-list.h"
#include <iostream>
#include <new>
using namespace std;
DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = NULL;
    prev = NULL;
}
DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}
/*DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list)
:size_(list.size_)
{
	


}
*/
DoublyLinkedList::~DoublyLinkedList()
{
    Node* curr = head_;
    while(curr){
        head_ = curr->next;
        delete curr;
        curr = head_;
    }
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}
bool DoublyLinkedList::empty() const
{
    if(!head_) return true; // no head means no list
    return false;

}
unsigned int DoublyLinkedList::size() const
{
    return size_;

}
void DoublyLinkedList::print() const
{
    if(head_) {
        Node *curr = head_;
        cout << curr << " ";
        while (curr->next != NULL) {
            cout << curr->next << " ";
            curr = curr->next;
        }
    }

}
bool DoublyLinkedList::insert_front(DataType value)
{
    if(!head_){    //0 element list
        head_ = new Node(value);
        tail_ = head_;
        size_ = 1;
        return true;
    }
    else if(size_ == 1) {  //1 element list
        head_->prev = new Node(value);
        head_ = tail_->prev;
        head_->next = tail_;
        size_ += 1;
        return true;
    }

        Node* curr = head_; //1+ element list
        curr->prev = new Node(value);
        head_ = curr->prev;
        head_->next = curr;
        size_ += 1;
        return true;
    }


bool DoublyLinkedList::remove_front()
{
    if(!head_){   //if there is no element
        return false;
    }
    else if(size_== 1){  //if there is only one element
        Node* curr = head_;
        head_ = NULL;
        tail_ = NULL;
        size_ = 0;
        delete curr;

        return true;
    }
    if(head_->next){     // if theres more than 1 element
        Node* curr = head_;
        head_ = curr->next;
        head_->prev = NULL;
        delete curr;
        size_ -= 1;
        return true;
    }


}
bool DoublyLinkedList::insert_back(DataType value)
{
    if(size_ == 0){  //0 element list
        head_ = new Node(value);
        tail_ = head_;
        size_ = 1;
        return true;
    }
    else if(size_ != 0) {   //1+ elements in the list
        Node *curr = new Node(value);
        curr->prev = tail_;
        tail_->next = curr;
        tail_ = curr;
        size_ += 1;
        return true;
    }
}
bool DoublyLinkedList::remove_back()
{
    if(!head_){ //no element list
        return false;
    }
    else if(size_ == 1){ // 1 element list
        Node* curr = head_;
        delete curr;
        head_ = NULL;
        tail_ = NULL;
        size_ = 0;
        return true;
    }
        Node* curr = tail_; //1+ element list
        tail_ = tail_->prev;
        delete curr;
        tail_->next = NULL;
        size_ -= 1;
        return true;

}
bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if(index > size_) return false; //invalid case
    if(index == 0){                 //insert front
        return insert_front(value);
    }
    else if(index == size_){        //insert back
        return insert_back(value);
    }
    Node* newNode = new Node(value);  //insert elsewhere
    Node* curr = head_;
    for(int i = 0; i < index - 1; i++){
        curr = curr->next;
    }
    newNode->next = curr->next;
    newNode->prev = curr;
    (curr->next)->prev = newNode;
    curr->next = newNode;
    size_ += 1;

    return true;



}
bool DoublyLinkedList::remove(unsigned int index)
{
    if(!head_ || index >= size_){   //empty list or invalid
        return false;
    }
    else if(index == 0){  //remove front
        return remove_front();
    }
    else if(index == (size_ - 1)){ //remove back
        return remove_back();
    }
    Node* curr = head_;  //remove elsewhere
    Node* tempPrev = NULL;
    Node* tempNext = NULL;
    for(int i = 0; i < index; i++){
        curr = curr->next;
    }
    tempPrev = curr->prev;
    tempNext = curr->next;
    delete curr;
    tempPrev->next = tempNext;
    tempNext->prev = tempPrev;
    return true;

}
unsigned int DoublyLinkedList::search(DataType value) const
{

    Node* curr = head_;
    for(unsigned int i = 0; i < size_; i++){ //i iterates until value is found or at end of the list
        if(curr->value == value){
            return i;
        }
        curr = curr->next;
    }
    return size_; // if empty

}
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if(index >= size_){ //invalid case
        return getNode(size_ - 1)->value;
    }

    return getNode(index)->value;


}
bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if(index < size_) { // if valid
        Node *curr = getNode(index);
        curr->value = value;
        return true;
    }
    return false; //if invalid


}
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
   if(index >= size_) return NULL; //index doesnt exist
   else {
       Node *curr = head_;
       for (int i = 0; i < index; i++) { //iterate to index and return pointer to node at index
           curr = curr->next;
       }

       return curr;
   }
}
bool DoublyLinkedList::full() const
{
    if(size_ == CAPACITY) return true;
    return false;

}
