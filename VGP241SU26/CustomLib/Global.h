#pragma once
#include <string>
#include <functional>
#include "Vector.h"

class Global
{
public:
	// Hash Funtion
	static std::size_t HashFunction(const std::string& str)
	{
		std::size_t hash = 0;

		for (std::size_t i = 0; i < str.size(); ++i)
		{
			hash = (~hash << i) + (std::size_t)(str[i]);
		}

		return hash;
	}

	// Swap
	template<typename T>
	static void Swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	// Bubble Sort
	template<typename T, typename Compare = std::less<T>>
	static void BubbleSort(Vector<T>& values, Compare sortFunc = Compare{})
	{
		std::size_t size = values.Size();

		for (std::size_t i = 0; i < size - 1; ++i)
		{
			for (std::size_t j = 0; j < size - 1; ++j)
			{
				if (sortFunc(values[j + 1], values[j]))
				{
					Swap(values[j + 1], values[j]);
				}
			}
		}
	}

	// Selection Sort
	template<typename T, typename Compare = std::less<T>>
	static void SelectionSort(Vector<T>& values, Compare sortFunc = Compare{})
	{
		std::size_t size = values.Size();

		for (std::size_t i = 0; i < size - 1; ++i)
		{
			std::size_t minIdx = i;

			for (std::size_t j = i + 1; j < size; ++j)
			{
				if (sortFunc(values[j], values[minIdx]))
				{
					minIdx = j;
				}
			}

			if (i != minIdx)
			{
				Swap(values[i], values[minIdx]);
			}
		}
	}
};