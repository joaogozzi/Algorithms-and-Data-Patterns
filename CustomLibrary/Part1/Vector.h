#pragma once
#include <cstddef>
#include <utility>
#include <cassert>

#include "ContainerIterator.h"

template<typename T>
class Vector
{
public:

	Vector()
		: mValues(nullptr),
		mCapacity(0),
		mSize(0)
	{}

	~Vector()
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}

		mCapacity = 0;
		mSize = 0;
	}

	Vector(const Vector& other)
	{
		if (other.mCapacity > 0)
		{
			mValues = new T[other.mCapacity];

			for (size_t i = 0; i < other.mCapacity; ++i)
			{
				mValues[i] = other.mValues[i];
			}
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}

		if (other.mCapacity > 0)
		{
			mValues = new T[other.mCapacity];

			for (size_t i = 0; i < other.mCapacity; ++i)
			{
				mValues[i] = other.mValues[i];
			}
		}

		mCapacity = other.mCapacity;
		mSize = other.mSize;
		return *this;
	}

	Vector(Vector&& other)
	{
		mValues = std::move(other.mValues);
		mCapacity = other.mCapacity;
		mSize = other.mSize;

		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;
	}

	Vector& operator=(Vector&& other)
	{
		if (mValues != nullptr)
		{
			delete[] mValues;
			mValues = nullptr;
		}

		mValues = std::move(other.mValues);
		mCapacity = other.mCapacity;
		mSize = other.mSize;

		other.mValues = nullptr;
		other.mCapacity = 0;
		other.mSize = 0;

		return *this;
	}

	// Reserve - pre allocate a chunk of data as long as it is greater than the current capacity
	void Reserve(size_t capacity)
	{
		if (capacity > mCapacity)
		{
			T* newValues = new T[capacity];

			if (mValues != nullptr)
			{
				for (size_t i = 0; i < mSize; ++i)
				{
					newValues[i] = value[i];
				}
			}

			delete[] mValues;
			mValues = std::move(newValues);
			mCapacity = capacity;
		}
	}

	// Resize - it creates the container of data
	//  can be larger/smaller than capacit
	//  sets capacity to resized value
	//  removes/deletes items above new capacity
	void Resize(size_t size, const T& initialValue = T())
	{
		if (size == mSize)
			return;

		if (size < mSize)
		{
			// destroy elements above current size
			for (size_t i = size; i < mSize; ++i)
			{
				// call destructor of unused elements
				mValues[i].~T();
			}
		}
		else if (mSize < size)
		{
			std::size_t newCapacity = std::max(size, mCapacity);
			Reserve(newCapacity);

			for (size_t i = mSize; i < size; ++i)
			{
				mValues[i] = initialValue;
			}
		}

		mSize = size;
	}

	void Clear()
	{
		Resize(0);
	}

	size_t Size() const
	{
		return mSize;
	}

	size_t Capacity() const
	{
		return mCapacity;
	}

	void PushBack(const T& value)
	{
		if (mSize >= mCapacity)
		{
			//if capacity is 0, set a default min capacity or double current
			size_t newCapacity = (mCapacity == 0) ? 10 : mCapacity * 2;
			Reserve(newCapacity);
		}

		mValues[mSize] = value;
		++mSize;
	}

	void PopBack()
	{
		assert(mSize > 0, "No elements in the vector");
		Resize(mSize - 1);
	}

	T& operator[](size_t index)
	{
		assert(index < mSize, "index out of range");
		return mValues[index];
	}

	const T& operator[](size_t index) const
	{
		assert(index < mSize, "index out of range");
		return mValues[index];
	}

	// Iterator Section
	using Iterator = ContainerIterator<T>;
	using Const_Iterator = ContainerIterator<const T>;
	Iterator Begin() { return Iterator(mValues); }
	Iterator End() { return Iterator(mValues + _size); }
	Const_Iterator Begin() const { return Const_Iterator(mValues); }
	Const_Iterator End() const { return Const_Iterator(mValues + _size); }

private:
	T* mValues = nullptr;
	size_t mCapacity = 0;
	size_t mSize = 0;
};