//
// Created by tanny on 5/16/2020.
//

#include <iostream>
#include "cmath"
using std::cout;
using std::endl;

enum arrayCopyType {
    copyFirstArray = 1,
    copyBothArray = 2
};

class Sequence {
public:
   /* Default Constructor
    * POST:
    * 1.Creates an array of size 2 & assigns address to double array pointer
    * 2.Set maximum size to 2
    * 3.Set current size to 0
    * */
    Sequence();

    /* Copy Constructor
     * POST: Creates a deep copy of its constant Sequence reference parameter
     * */
    Sequence(const Sequence & sq);

    /* Destructor
     * POST: Deallocate dynamic memory associated with the object’s double (array) pointer
     * */
    ~Sequence();

    /* Overloaded Assignment Operator
     * PARAM:The sequence object which will be copied into the calling object(replacement)
     * POST:
     * 1. Returns a reference to the calling object
     * 2. Deallocates dynamic memory associated with the calling object's original array
     * */
    Sequence & operator=(const Sequence &sq);

    /* Insert
     * PARAM:Value - value that will be inserted to the end of the calling object's array
     * POST:
     * Special Case:A new array will be created to copy the old array in, when the calling object's maximum size is full.
     * Then,release the memory of the old array. Max size of the new array = 2 * calling object's maximum size
     * */
    void insert(double value);

    /* Insert
     * PRE:The value of insertedSize MUST be the exact number of elements contained in first parameter(insertedArr)
     * PARAM:Array that will be inserted to the end of the calling object's array and its size
     * POST:
     * Special Case:A new array will be created to copy the two arrays in, when the calling object's maximum size is not large enough.
     * Then,release the memory of the two old arrays.
     *  - Max size of the new array = max(calling object's max size, calling object's current size + inserted size).
     * */
    void insert(double insertedArr[],int insertedSize);

    /* Find
     * PARAM:The target which should be searched in the sequence.
     * POST: Return the number of sequence elements whose value is equal to the target.
     * */
    int find(double target) const;

    /* Size
     * POST: Return the number of values in the calling object.
     * */
    int size() const;

    /* Sum
     * POST: Return the sum of the values in the calling objects.
     * */
    double sum() const;

    /* Mean
     * POST: Return the average of the values in the calling object.
     * */
    double mean() const;

    /* Median
     * POST: Returns the median of the values in the calling object.
     * */
    double median() const;

    /* Standard Deviation
     * POST: Return the standard deviation of the values in the sequence.
     * */
    double stddev() const;

    /* Concatenate
     * PARAM:The sequence which will be concatenated to the calling object.
     * POST: Returns a Sequence object whose:
     * 1.Maximum Array Size = max(2,the number of values stored in it).
     * 2.Real Array Size = the number of values stored in it
     * 3.Array Content = Content of array in both calling object and sequence object in parameter.
     * */
    Sequence concatenate(const Sequence & sq) const;


private:
    /* A pointer points to the array of doubles */
    double *array;
    /* The number of values stored in the array */
    int arrSize;
    /* Maximum size of the array */
    int maxSize;

    /* Copy Sequence into Calling Object
     * POST: It replaces all the content of calling object with the content of the sequence object in the parameter
     * */
    void copySequence(const Sequence & sq);

    /* Array Generator
     * [PRE]:Two Mode Here
     * 1.Type = CopyFirstArray(default): Simply deeply copy first array into the new array.
     * 2.Type = CopyBothArray: Deeply copy both two array into the new array
     * (firstArrSize + secondArrSize) is the minimum valid value for this function.so if assigned,newArrSizeIfNeeded >= that[MUST!]
     * NOTE:The value of array size(for both 'firstArrSize' and 'secondArrSize')
     * MUST be the exact number of elements contained in corresponding array parameters!
     * MUST check all the functions using this sub-function and release this returning result in time when no longer needed!
     * [PARAM]:
     * 1.firstArr & firstArrSize: The array which will be deeply copied into new array and its size.
     * 2.secondArr(default:nullptr),secondArrSize(default:0):The array which will be deeply copied into new array and its size.
     * 3.newArrSizeIfNeeded:If assigned, the value will be the max size of the newArray
     * NOTE:Its default value = 0, in this case we simply set the max size of the new array as the sum of size of copied array(arrays)
     * [POST]:
     * - Return a double array pointer which point to the new array.
     * - Size of new array = sum of size of copied array(arrays)
     * - The maxSize of new array = max((firstArrSize+secondArrSize), newArrSizeIfNeeded)
     * * */
    double* deepCopyArray(const double* firstArr, int firstArrSize, int newArrSizeIfNeeded=0, const double* secondArr = nullptr, int secondArrSize = 0, arrayCopyType type = copyFirstArray)const;

    /* PARAM:The array pointer which was pointing to the memory area that will be release in this function.
     * POST:
     * 1.Release the memory allocated for the array which was pointed by arr pointer
     * 2.Make arr point to nullptr.
     * */
    void releaseArray(double* arr);

    /* Sum
     * PRE: The value of arraySize MUST be the exact number of elements contained in first parameter(arr)
     * PARAM:The array whose elements should be calculated and its size.
     * POST: Return the sum of the values in the calling objects.
     * */
    double sum(const double * arr, int arraySize) const;

    /* Sort(Min to Max)
     * PRE: The value of arraySize MUST be the exact number of elements contained in first parameter(arr)
     * PARAM:The array whose elements should be sorted and its size.
     * POST: The order of the array's elements will be well-organised(min to max).
     * */
    void sort(double* arr, int arraySize) const;

};

