#include "sequential-list.h"
#include <iostream>

using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType[capacity_]; //data_ points dynamically to an array on the heap with space = capacity
}

SequentialList::~SequentialList()
{
    delete data_;
    data_ = NULL;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if(size_ == 0)return true;
    return false;
}

bool SequentialList::full() const
{
    if(size_ == capacity_)return true;
    return false;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if(index >= size_) return data_[size_ - 1]; //if index invalid
    return data_[index];
}

unsigned int SequentialList::search(DataType val) const
{
    for(int i = 0; i < size_; i++){ //iterates until value is found, returns index
        if(data_[i] == val) return i;
    }
    return size_; //if not found
}

void SequentialList::print() const
{
    for(int i = 0; i < size_; i++){
        cout << data_[i] << " ";
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if(index == size_ && size_ != capacity_){ //insert back
       return insert_back(val);

    }
    else if(index < size_ && size_ != capacity_){ // insert elsewhere... moving elements behind down by 1
        for(unsigned int i = size_; i > index; i--){
            data_[i] = data_[i - 1];
        }
        data_[index] = val;
        size_ += 1;
        return true;
    }
    return false; // if invalid

}

bool SequentialList::insert_front(DataType val)
{
    if(size_ != capacity_ && size_ == 0){ // if empty list
        data_[size_] = val;
        size_ += 1;
        return true;
    }
    else if(size_ != capacity_ && size_ > 0){ //if nonempty list... moves elements back and inserts at front
        for(unsigned int i = size_; i > 0; i--){
            data_[i] = data_[i - 1];
        }
        data_[0] = val;
        size_ += 1;
        return true;
    }
    return false; //if invalid
}

bool SequentialList::insert_back(DataType val)
{
    if(size_ != capacity_ && size_ == 0){ //empty list
        data_[size_] = val;
        size_ += 1;
        return true;
    }
    else if(size_ != capacity_){ //nonempty list
        data_[size_] = val;
        size_ += 1;
        return true;
    }
    return false; //if invalid
}

bool SequentialList::remove(unsigned int index)
{
    if(size_ == 0) return false;
    else if(index == (size_ - 1)){
        return remove_back();
    }
    else if(index < size_){
        data_[index] = NULL;
        for(unsigned int i = index; i < size_; i++){
            data_[i] = data_[i + 1];
        }
        size_ -= 1;
        return true;
    }
    return false;
}

bool SequentialList::remove_front()
{
   if(size_ == 0) return false; //returns true if there isn't a front to begin with

       for(int i = 0; i < size_; i++){
           data_[i] = data_[i + 1];        //pushes remaining elements forward by 1
       }
       size_ -= 1;
       return true;

}

bool SequentialList::remove_back()
{
   if(size_ == 0) return true;
   else if(size_ != 0){
       data_[size_ - 1] = 0;
       size_ -= 1;
       return true;
   }
   return false;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if(index < size_ ){ // if exists
        data_[index] = val;
        return true;
    }
    return false; //if invalid
}

