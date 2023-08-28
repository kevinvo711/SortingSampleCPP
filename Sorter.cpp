/****************************************************************************************************************************
Title          :   Sorter.cpp
Auhor          :   Nigel Ferrer
Modified By    :   Kevin Vo
Description    :   implementation file of an integer array container class that
                   contains implementations of some sorting algorithms
Dependencies   :   Sorter.cpp
****************************************************************************************************************************/

#include "Sorter.hpp"
using namespace std;

Sorter::Sorter(array_type type, size_t array_size, int *arr) : type_(type), SIZE_(array_size), values_(arr)
{
}

/***************************s* Selection Sort ****************************/
template <typename Comparator>
int Sorter::getPosOfMinOrMax(int arr[], int from, int to, const Comparator &comp)
{
    int min_or_max = from;
    for (int i = from + 1; i <= to; i++)
    {
        if (comp(arr[i], arr[min_or_max]))
        {
            min_or_max = i;
        }
    }
    return min_or_max;
}

template <typename Comparator>
int Sorter::selectionSort(int arr[], size_t size, const Comparator &comp)
{
    int absMax = 0;
    for (int i = 0; i < size - 1; i++)
    {
        absMax = getPosOfMinOrMax(arr, i, size - 1, comp);
        for (int j = i + 1; j < size; j++)
        {
            // cout << j << ": " << "absMax is: " << absMax << " value is: " << arr[absMax] <<endl;

            if (comp(arr[j], arr[absMax]))
            {
                // cout << "arr[j] is: " << arr[j] << " and arr[absMax] is: " << arr[absMax] << endl;
                absMax = j;
            }
        }
        int hold = arr[i];
        arr[i] = arr[absMax];
        arr[absMax] = hold;
        selectionCount_++;
    }
    return selectionCount_;
}
/************************************************************************/

/**************************** Insertion Sort ****************************/
template <typename Comparator>
int Sorter::insertionSort(int arr[], size_t size, const Comparator &comp)
{
    // outer loop will produce partially sorted elements until end
    for (int i = 0; i < size; i++)
    {

        // loop through remainder of unsorted array
        for (int j = i + 1; j < size; j++)
        {
            if (comp(arr[j], arr[i]))
            {
                // swap if there is a comparison
                int hold = arr[i];
                arr[i] = arr[j];
                arr[j] = hold;

                insertionCount_++;
            }
        }
    }
    return insertionCount_;
}
/************************************************************************/

// /****************************** Merge Sort ******************************/
template <typename Comparator>
void Sorter::merge(int arr[], int from, int mid, int to, const Comparator &comp)
{
    int tempArray[SIZE_];   //temp array with max size of array given by constructor
    int first1 = from;      //beginning of first subarray
    int last1 = mid;        //end of first subarray
    int first2 = mid + 1;   //beginning of second subarray
    int last2 = to;         //end of second subarray

    // while both subarrays are not empty, copy smaller item into temp array
    int index = first1; //next available location in temp array
    while((first1 <= last1) && (first2 <= last2)){
        //at this point, tempArray[first ... index-1] is in order
        if(arr[first1] <= arr[first2]){
            tempArray[index] = arr[first1];
            first1++;
        } else {
            tempArray[index] = arr[first2];
            first2++;
        }
        index++;
    }

    //finish off first subarray if needed
    while(first1 <= last1){
        // at this point, tempArray[first ... index-1] is in order
        tempArray[index] = arr[first1];
        first1++;
        index++;
        mergeCount_++;
    }

    while(first2 <= last2){
        // at this point, tempArray[first ... index-1] is in order
        tempArray[index] = arr[first2];
        first2++;
        index++;
        mergeCount_++;
    }

    //copy result back into original array
    for(index = from; index <= to; index++){
        arr[index] = tempArray[index];
    }
}

template <typename Comparator>
int Sorter::mergeSort(int arr[], int from, int to, const Comparator &comp)
{
    if(from < to){
        //sort each half
        int mid = from + (to - from) / 2;

        //sort left half of arr[first...mid]
        mergeSort(arr, from, mid, comp);

        //sort right half of arr[mid+1...last]
        mergeSort(arr, mid + 1, to, comp);

        //merge the halves
        merge(arr, from, mid, to, comp);
    }
    return mergeCount_;
}
// /************************************************************************/

void Sorter::runSorts(sort_order order)
{

    int selectionValues[SIZE_];
    int insertionValues[SIZE_];
    int mergeValues[SIZE_];

    if (type_ == RANDOM)
    {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = rand() % 100;
            insertionValues[i] = rand() % 100;
            mergeValues[i] = rand() % 100;
        }
    }

    else
    {
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = values_[i];
            insertionValues[i] = values_[i];
            mergeValues[i] = values_[i];
        }
    }

    // Selection Sort Display
    std::cout << "******** Selection Sort ********\nOriginal Array:\n";
    displayArr(selectionValues);
    if (order == INCREASING)
    {
        selectionSort(selectionValues, SIZE_, std::less<int>());
    }
    else
    {
        selectionSort(selectionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(selectionValues);
    std::cout << "\nNumber of swaps: " << selectionCount_ << "\n********************************\n\n";

    // Insertion Sort Display
    std::cout << "\n******** Insertion Sort ********\nOriginal Array:\n";
    displayArr(insertionValues);
    if (order == INCREASING)
    {
        insertionSort(insertionValues, SIZE_, std::less<int>());
    }
    else
    {
        insertionSort(insertionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(insertionValues);
    std::cout << "\nNumber of swaps: " << insertionCount_ << "\n********************************\n\n";

    // Merge Sort Display
    std::cout << "\n********** Merge Sort **********\nOriginal Array:\n";
    displayArr(mergeValues);
    if (order == INCREASING)
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::less<int>());
    }
    else
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(mergeValues);
    std::cout << "\nNumber of comparisons: " << mergeCount_ << "\n********************************\n\n";
}

void Sorter::displayArr(const int array[]) const
{
    for (size_t i = 0; i < SIZE_; i++)
    {
        std::cout << array[i];
        (i < SIZE_ - 1) ? (cout << " ") : (cout << "\n");
    }
}