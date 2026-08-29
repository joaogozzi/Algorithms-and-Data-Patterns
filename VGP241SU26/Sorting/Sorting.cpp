#include <iostream>
#include <Global.h>
#include <time.h>

void PrintIntVec(Vector<int>& numbers)
{
    for (int i = 0; i < numbers.Size(); ++i)
    {
        std::cout << numbers[i] << " ";
    }

    std::cout << "\n";
}

void ExerciseInsertion()
{
    std::cout << "Insertion Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::InsertionSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

void ExerciseMerge()
{
    std::cout << "Merge Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::MergeSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

void ExerciseQuickSort()
{
    std::cout << "Quick Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::QuickSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

void ExerciseBucketSort()
{
    std::cout << "Bucket Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::BucketSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

void ExerciseHeapSort()
{
    std::cout << "Heap Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::HeapSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

void ExerciseIntroSort()
{
    std::cout << "Intro Sort:\n";
    Vector<int> numbers;

    for (int i = 0; i < 20; ++i)
    {
        int value = 1 + (rand() % 100);
        numbers.PushBack(value);
        std::cout << value << " ";
    }

    std::cout << "\n";
    std::cout << "Sorted:\n";
    Global::IntroSort(numbers.Begin(), numbers.End());
    PrintIntVec(numbers);
}

int main()
{
    srand(time(0));
    //ExerciseInsertion();
    //ExerciseMerge();
    //ExerciseQuickSort();
    //ExerciseBucketSort();
    //ExerciseHeapSort();
    ExerciseIntroSort();

    return 0;
}
