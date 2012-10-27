#include "dataVector.h"
#include <vector>
#include <cstring>

using namespace std;


void DataVector::Write(long offset, const void *src, long size){
    if (offset + size >= this->size())
        this->resize(offset+size);
    for (long i=0; i<size; i++) {
        (*this)[i] = 
                   reinterpret_cast<const unsigned char *>(src)[i];
    }
}

void DataVector::Put(long offset, unsigned char c) {
    if (offset >= this->size())
        this->resize(offset);
    (*this)[offset] = c;
}

void DataVector::Fill(long offset, unsigned char c, long count){
    if (offset + this->Size() >= this->size())
        this->resize(offset+this->Size());
    for (long i=0; i<this->Size(); i++) {
        (*this)[i] = c;
    }
}

void DataVector::Read(long offset, void *dest, long size) const {
    memcpy(dest,this->data(),size);
}

unsigned char DataVector::Get(long offset) const {
    return (*this)[offset];
}

void DataVector::ReadString(long offset, std::string& dest)const {
    dest = reinterpret_cast<const char *>(this->data());
}

long DataVector::Size()const {
    return this->size();
}

long DataVector::Next( long offset, unsigned char c) const {
    long i;
    for (i = offset; i < this->size(); ++i) {
        if ( (*this)[i] == c ) 
            return i;
    }
    return i;
}

long DataVector::Last( long offset, unsigned char c) const {
    long i;
    for (i = offset; i >= 0; --i) {
        if ( (*this)[i] == c ) 
            return i;
    }
    return i;
}