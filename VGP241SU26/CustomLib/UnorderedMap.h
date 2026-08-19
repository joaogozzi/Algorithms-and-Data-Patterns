#pragma once
#include <algorithm>
#include <functional>
#include "Vector.h"

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
	struct KeyValuePair
	{
		KeyType key;
		ValueType value;
	};

public:
	UnorderedMap(std::size_t initialBucketSize = 8, double loadFactor = 0.8)
		: mLoadFactorThreashold(loadFactor),
		mCount(0)
	{
		mBucketCount = std::max<std::size_t>(initialBucketSize, 1);
		mTable.Resize(mBucketCount);
	}

	// Delete copy/moves
	// Prevents duplicating or losing content
	UnorderedMap(const UnorderedMap&) = delete;
	UnorderedMap(UnorderedMap&&) = delete;

	UnorderedMap& operator=(const UnorderedMap&) = delete;
	UnorderedMap& operator=(UnorderedMap&&) = delete;

	void Insert(const KeyType& key, const ValueType& value)
	{
		std::size_t index = GetTableIndex(key);

		// Check if already added
		const Vector<KeyValuePair*>& bucket = mTable[index];
		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				// If already added, update the value and return
				bucket[i]->value = value;
				return;
			}
		}

		// Otherwise add the new keyValue pair
		KeyValuePair* kv = new KeyValuePair();
		kv->key = key;
		kv->value = value;
		mTable[index].PushBack(kv);
		++mCount;

		if ((double)mCount / (double)mBucketCount > mLoadFactorThreashold)
		{
			// If too many items, very possible too many collisions, resize and rehash index locations
			Rehash();
		}
	}

	bool Find(const KeyType& key, ValueType& outValue) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = mTable[index];

		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				outValue = bucket[i]->value;
				return true;
			}
		}

		return false;
	}

	bool Has(const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = mTable[index];

		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
				return true;
		}

		return false;
	}

	bool Remove(const KeyType& key)
	{
		std::size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = mTable[index];

		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				KeyValuePair* tmp = bucket[i];
				bucket[i] = bucket[bucket.Size() - 1];
				bucket[bucket.Size() - 1] = tmp;

				delete tmp;
				tmp = nullptr;

				bucket.PopBack();
				return true;
			}
		}

		return false;
	}

	std::size_t Count() const
	{
		return mCount;
	}

	void Clear()
	{
		for (std::size_t t = 0; t < mTable.Size(); ++t)
		{
			Vector<KeyValuePair*>& bucket = mTable[t];

			for (std::size_t b = 0; b < bucket.Size(); ++b)
			{
				delete bucket[b];
				bucket[b] = nullptr;
			}

			bucket.Clear();
		}

		mCount = 0;
	}

	// data accessors (operators)
	ValueType& operator[](const KeyType& key)
	{
		// Do I have it, if so return ref
		if (!Has(key))
		{
			// Insert default so there is a value
			Insert(key, mDefault);
		}

		std::size_t index = GetTableIndex(key);
		Vector<KeyValuePair*>& bucket = mTable[index];

		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}

		assert(false, "UnorderedMap: Key never gets added");
		return mDefault;
	}

	const ValueType& operator[](const KeyType& key) const
	{
		std::size_t index = GetTableIndex(key);
		const Vector<KeyValuePair*>& bucket = mTable[index];

		for (std::size_t i = 0; i < bucket.Size(); ++i)
		{
			if (bucket[i]->key == key)
			{
				return bucket[i]->value;
			}
		}

		return mDefault;
	}

private:
	std::size_t GetTableIndex(const KeyType& key) const
	{
		// If there is a resize, need to remove and re add all elements
		// The table index WILL change because the mBucketCount will increase
		return mHashFunction(key) % mBucketCount;
	}

	void Rehash()
	{
		// We will remove all items and add in the updated table indices
		std::size_t newBucketCount = mBucketCount * 2;
		Vector<Vector<KeyValuePair*>> newTable;
		newTable.Resize(newBucketCount);

		// Need to get everything from the old table, reposition and swap data over
		mBucketCount = newBucketCount;

		for (std::size_t t = 0; t < mTable.Size(); ++t)
		{
			Vector<KeyValuePair*>& bucket = mTable[t];

			for (std::size_t b = 0; b < bucket.Size(); ++b)
			{
				std::size_t index = GetTableIndex(bucket[b]->key);
				newTable[index].PushBack(bucket[b]);
			}

			bucket.Clear();
		}

		mTable = std::move(newTable);
		newTable.Clear();
	}

	// This is used if something can't be found and you can't return a nullptr
	ValueType mDefault;
	// Table is the main vector, "Bucket" is the vector of objects using the same index
	Vector<Vector<KeyValuePair*>> mTable;
	// Max indices the table can use to store individual values
	std::size_t mBucketCount = 0;
	// Total number of items in the table
	std::size_t mCount = 0;
	// How many items in the bucket before we need to resize the table
	double mLoadFactorThreashold = 1.0;
	// stl version of HashFunction to allow any type of key value to be hashed
	std::hash<KeyType> mHashFunction;
};