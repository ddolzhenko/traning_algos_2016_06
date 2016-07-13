#pragma once

#include "cassert"
#include "algorithm"

template <class T>
class my_vector
{
public:
   my_vector(size_t size = 0);
   my_vector(const my_vector<T>& rhs);
   ~my_vector();

   my_vector<T>& operator=(const my_vector<T>& that);
   void swap(my_vector<T>& other);// noexept;
   void reserve(size_t new_size);
   T& operator[](size_t index);
   T* begin();
   T* end();
   void push_back(const T& x);
   size_t size() const;

private:
   T*       mData;
   size_t   mSize;
   size_t   mCapacity;
};

//--------------------------DECLARATIONS----------------------------------

template <class T>
my_vector<T>::my_vector(size_t size = 0)
   : mData(nullptr)
   , mSize(0)
   , mCapacity(0)
{
   mData = new T[size];
   mSize = size;
   mCapacity = size;
}

template<class T>
my_vector<T>::my_vector(const my_vector<T>& rhs)
   : mData(nullptr)
   , mSize(0)
   , mCapacity(0)
{
   mData = new T[other.size()];
   mSize = other.size();
   mCapacity = other.capacity();
   std::copy(other.begin(), other.end(), mData);
}


template <class T>
my_vector<T>::~my_vector()
{
   delete[] mData;
}

template<class T>
void my_vector<T>::swap(my_vector<T>& other)
{
   std::swap(mData, other.data);
   std::swap(mSize, other.mSize);
   std::swap(mCapacity, other.mCapacity);
}

template<class T>
void my_vector<T>::reserve(size_t new_size)
{
   if (mCapacity < new_size)
   {
      T* tmp = new T[new_size];
      //std::copy(begin(), end(), tmp);
      memcpy(tmp, mData, mSize);
      delete[] mData;
      mData = tmp;
      mCapacity = new_size;
   }
}

template<class T>
T & my_vector<T>::operator[](size_t index)
{
   return mData[index];
}

template<class T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& that)
{
   if (this != &other)
      this->swap(vector<T>(other));   //copy swap idiom!
   return this;
}

template<class T>
T * my_vector<T>::begin()
{
   return mData;
}

template<class T>
T * my_vector<T>::end()
{
   return mData + mSize;
}

template<class T>
void my_vector<T>::push_back(const T & x)
{
   assert(mCapacity >= mSize);
   if (mCapacity == mSize)
   {
      reserve(mSize * 2 + 1);
   }
   *(end()) = x;
   ++mSize;
   assert(mCapacity >= mSize);
}

template<class T>
size_t my_vector<T>::size() const
{
   return mSize;
}
