//
// Created by tanny on 6/30/2020.
//

#include <vector>
#include <iostream>
using namespace std;
using std::cout;
using std::endl;

/* Exchange the value of array[i] and array[j]
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be exchange;
 *        - i&j = the indexes of elements in the array whose values need to be exchanged with each other.
 * POST : array[i]=array[j];  array[j]=array[i]
 * */
template<class T>
void exchange(T* array, int i, int j);

/* Sort an array with quick sort algorithm [Ascending]
 * PRE  :
 * PARAM: - array = the array(of any type) whose elements need to be sorted;
 *        - low/high = the first/last index of the part which need to be sorted in the array.
 *        - barometer = the number of times its barometer operation is executed
 * POST : Make elements of array sorted in ascending order
 * */
template<class T>
void qSortHelper(T* array, int low, int high,int &barometer);

/* Splits the array into two parts(smaller than key <-|* key *|->larger than key).
 * PRE  :
 * PARAM: - array = the array(of any type) whose elements need to be sorted;
 *        - low/high = the first/last index of the part which need to be sorted in the array.
 *        - barometer = the number of times its barometer operation is executed
 * POST : 1.[the left side]<--(smaller part) |KEY(pivot)| (the right part)-->[larger part]
 *        2. Return the index of the position where current key value(also the separator of two parts) was finally placed on.
 * */
template<class T>
int  partition (T* array, int low, int high,int &barometer);

/* Merge two ordered sequences into a sequence in ascending order.
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;
 *        - low/mid/high = the first/mid/last index of the part which need to be sorted in the array.
 * POST : 1.Merge two ordered sequences into a single sequence in ascending order
 *        2.Return the number of times its barometer operation is executed
 * */
template<class T>
int merge(T* array, int low, int mid, int high);



// -------------------------------------------------  Insertion Sort  ---------------------------------------------
/* Sort an array with insertion algorithm [Ascending]
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;  - size = size of array
 * POST : Make elements of array sorted in ascending order, and return the number of times that its barometer operation is executed
 * */
template<class T>
int insertionsort(T* arr, int size){
    int barometer = 0;
    T key;
    for(int i = 1; i < size; ++i){
        //keep the key value to avoid losing it.
        key = arr[i];
        int pos = i;
        // compare all sorted items to key, store its value to the right position if its value > key
        while(pos > 0 && (arr[pos-1] > key)){
            ++barometer;
            arr[pos] = arr[pos-1];
            pos--;
        }
        //the comparisons(barometer: pos > 0 && (arr[pos-1] > key)) will go 'one time' more than the inner block
        ++barometer;
        // insert key
        arr[pos] = key;
    }
    return barometer;
}

// -------------------------------------------------  Quick Sort  ---------------------------------------------
/* Sort an array with quick sort algorithm [Ascending]
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;  - size = size of array
 * POST : Make elements of array sorted in ascending order, and return the number of times its barometer operation is executed
 * */
template<class T>
int quicksort(T* arr,int size){
    int barometer = 0;
    int low = 0;
    int high = size - 1;
    qSortHelper(arr,low,high,barometer);
    return barometer;
}

/* Sort an array with quick sort algorithm [Ascending]
 * PRE  :
 * PARAM: - array = the array(of any type) whose elements need to be sorted;
 *        - low/high = the first/last index of the part which need to be sorted in the array.
 *        - barometer = the number of times its barometer operation is executed
 * POST : Make elements of array sorted in ascending order
 * */
template<class T>
void qSortHelper(T* array, int low, int high,int &barometer){
    if (low < high){
        int indexOfSeparator = partition(array, low, high,barometer);
        qSortHelper(array, low, indexOfSeparator-1,barometer);
        qSortHelper(array, indexOfSeparator + 1, high,barometer);
    }
}


/* Splits the array into two parts(smaller than key <-|* key *|->larger than key).
 * PRE  :
 * PARAM: - array = the array(of any type) whose elements need to be sorted;
 *        - low/high = the first/last index of the part which need to be sorted in the array.
 *        - barometer = the number of times its barometer operation is executed
 * POST : 1.[the left side]<--(smaller part) |KEY(pivot)| (the right part)-->[larger part]
 *        2. Return the index of pivot(it is also the separator of two parts) where it is finally placed on.
 * */
template<class T>
int partition (T* array, int low, int high,int &barometer){
    //pivot
    T key = array[high];
    // i = the last index(rightmost) of smaller part,it acts as a 'wall' for the two parts.
    int i = (low - 1);

    // p is a probe, it will go through low to high-1 to find smaller elements(than key), if found, it will
    // call i('wall' of smaller part) to follow forward for one step, then assign the smaller value to array[i],
    // this kind of values finally form the set of smaller parts
    int p = low;
    while (p < high){
        ++barometer;
        if (array[p] <= key){
            //smaller elements(than key value) found, move i for 1 step forward,then assign array[i] with
            // the smaller value from 'probe' p, and throw the possible 'bigger' value to probe p.
            i = i + 1;
            exchange(array,i,p);
        }
        p = p + 1;
    }
    //the comparisons(barometer: p < high) will go 'one time' more than the inner block
    ++barometer;

    //i is the last index of smaller part and all the values after it are not smaller than key(pivot).
    //then position of key value has been fixed.
    int finalIndexOfKey = i + 1;
    exchange(array,finalIndexOfKey, high);
    return finalIndexOfKey;
}

// -------------------------------------------------  Merge Sort  ---------------------------------------------
/* Sort an array with merge sort algorithm [Ascending]
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;  - size = size of array
 * POST : Make elements of array sorted in ascending order, and return the number of times its barometer operation is executed
 * */
template<class T>
int mergesort(T* arr, int size){
    int barometer = 0;
    // in iteration, we start from the smallest step
    int step = 1;
    while (step < size){
        // step = 1 -> offset = 2 -> handle each 2 items
        int offset = step * 2;
        for (int lowPos = 0; lowPos < size - 1; lowPos = lowPos + offset) {
            int midPos =  ((lowPos + step - 1)<(size - 1))?(lowPos + step - 1):(size - 1);
            int highPos = ((lowPos + offset - 1)<(size - 1))?(lowPos + offset - 1):(size - 1);
            barometer = barometer + merge(arr, lowPos, midPos, highPos);
        }
        // each time, step will be doubled
        step = step * 2;
    }
    return barometer;
}

/* Merge two ordered sequences into a sequence in ascending order.
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;
 *        - low/mid/high = the first/mid/last index of the part which need to be sorted in the array.
 * POST : 1.Merge two ordered sequences into a single sequence in ascending order
 *        2.Return the number of times its barometer operation is executed
 * */
template<class T>
int merge(T* array, int low, int mid, int high){
    int barometer = 0;
    //probes for the left sub-array
    int leftLow = low;
    int leftHigh= mid;
    int p1 = leftLow;

    //probes for the right sub-array
    int rightLow = mid + 1;
    int rightHigh = high;
    int p2 = rightLow;

    //to put the result of sorted part
    std::vector <T> temp;
    //merge from left and right sub-arrays -> stop when one of the subarray goes to the end of iteration
    while (p1 <= leftHigh && p2 <= rightHigh){
        if (array[p1] < array[p2]){
            temp.push_back(array[p1]);
            p1++;
        }else{
            temp.push_back(array[p2]);
            p2++;
        }
    }
    //put the remaining of the left sub-array into container
    while(p1 <= leftHigh){
        temp.push_back(array[p1]);
        p1++;
    }
    //put the remaining of the right sub-array into container
    while (p2 <= rightHigh){
        temp.push_back(array[p2]);
        p2++;
    }
    for(unsigned int i = 0; i < temp.size(); ++i){
        ++barometer;
        array[i + low] = temp[i];
    }
    //the comparisons(barometer: i < temp.size()) will go 'one time' more than the inner block
    ++barometer;
    return barometer;
}

// -------------------------------------------------  Shell Sort  ---------------------------------------------
/* Sort an array with shell sort algorithm [Ascending]
 * PRE  : reference - https://www.includehelp.com/cpp-tutorial/implement-shell-sort-using-cpp-program.aspx
 * PARAM: - arr = the array(of any type) whose elements need to be sorted;  - size = size of array
 * POST : Make elements of array sorted in ascending order, and return the number of times its barometer operation is executed
 * */
template<class T>
int shellsort(T* array,int size){
    int barometer = 0;
    //gap will be halved for each time
    for(int gap = size / 2; gap > 0; gap /= 2){
        for(int i=gap; i < size;i++){
            //keep the key value to avoid losing it
            T key = array[i];
            int j;
            //values with an interval length -- 'gap' forms a 'sorted sequence'
            //shift and move the former elements and find a proper position for key
            for(j = i; j >= gap && array[j-gap] > key; j -= gap){
                //NOTE:the barometer operation here depends on the array condition. If this block never runs, then the
                //the barometer operation we choose here may not be the one which executed most frequently.
                ++barometer;
                array[j] = array[j-gap];
            }
            //insert key
            array[j] = key;
            //the comparisons(barometer: j >= gap && array[j-gap] > key) will go 'one time' more than the inner block
            ++barometer;
        }
    }
    return barometer;
}

// -------------------------------------------------  Others  ---------------------------------------------
/* Exchange the value of array[i] and array[j]
 * PRE  :
 * PARAM: - arr = the array(of any type) whose elements need to be exchange;
 *        - i/j = the indexes of elements in the array whose values need to be exchanged with each other.
 * POST : array[i]=array[j];  array[j]=array[i]
 * */
template<class T>
void exchange(T* array, int i, int j){
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

