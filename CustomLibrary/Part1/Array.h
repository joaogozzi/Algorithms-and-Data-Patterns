#pragma once
#include <cstddef>
#include <utility>

#include "ContainerIterator.h"

template<typename T, std::size_t N>
class Array
{
public:
	// Base constructor, called by default
	Array()
	{
		//will generate a dimension
		static_assert(N > 0, "Array must be at least 1");

		// allocate memory
		// size required is size of T, which is the type if the object
		// * the number of items, N
		mValues = new T[N];
	}

	Array(T initialValue)
	{
		static_assert(N > 0, "Array must be at least 1");
		mValues = new T[N];

		for (size_t i = 0; i < N; ++i)
		{
			mValues[i] = initialValue;
		}
	}

	// Destructor
	~Array()
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}
	}

	// copy constructor (called on creation)
	// copies the information of another same sized array
	Array(const Array& other)
	{
		mValues = new T[N];

		for (size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}
	}

	// copy operator (after creation, so may have data)
	// copies the information of another same sized array
	Array& operator=(const Array& other)
	{
		//if you have an array of objects that have pointers or data,
		// that data needs to be released or memory leak
		if (mValues !+ nullptr)
		{
			delete[] mValues;
		}

		mValues = new T[N];
		for (size_t i = 0; i < N; ++i)
		{
			mValues[i] = other.mValues[i];
		}

		return *this;
	}

	// move constructor(called on creation)
	Array(Array&& other)
	{
		// not deleting the data, changing ownership
		mValues = std::move(other.mValues);
		// clearing the info
		other.mValues = nullptr;
	}

	// move operator (called after creation)
	Array& operator=(Array&& other)
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
		}

		mValues = std::move(other.mValues);
		other.mValues = nullptr;

		return *this;
	}

	// get the number of elements (make it const after the function so it can be called if array is const)
	const std::size_t Size() const
	{
		return N;
	}

	// get the stored data
	T* Data()
	{
		return mValues;
	}

	// const value
	const T* Data() const
	{
		return mValues;
	}

	//operator overload []
	T& operator[](std::size_t index)
	{
		// can throw assert if out of range
		return mValues[index];
	}

	const T& operator[](std::size_t index) const
	{
		return mValues[index];
	}

	// Iterator Section
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + N); }
	Const_Iterator Begin() const { return Const_Iterator(mValues); }
	Const_Iterator End() const { return Const_Iterator(mValues + N); }

private:
	// T is the type we declare
	// pointer to a section of memory where the array is built
	T* mValues = nullptr;
};