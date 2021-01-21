//
// Created by tanny on 5/16/2020.
//

#include "Sequence.h"
/* Default Constructor
 * POST:
 * 1.Creates an array of size 2 & assigns address to double array pointer
 * 2.Set maximum size to 2
 * 3.Set current size to 0
 * */
Sequence::Sequence(){
    array = new double [2];
    maxSize = 2;
    arrSize = 0;
};

/* Copy Constructor
 * POST: Creates a deep copy of its constant sequence reference parameter
 * */
Sequence::Sequence(const Sequence & sq) {
    copySequence(sq);
}

/* Destructor
 * POST: Deallocate dynamic memory associated with the object’s double (array) pointer
 * */
Sequence::~Sequence(){
    releaseArray(array);
}

/* Overloaded Assignment Operator
 * PARAM:The sequence object which will be copied into the calling object(replacement)
 * POST:
 * 1. Returns a reference to the calling object
 * 2. Deallocates dynamic memory associated with the calling object's original array
 * */
Sequence & Sequence::operator=(const Sequence &sq) {
    if(this != &sq){
        releaseArray(array);
        copySequence(sq);
    }
    return *this;
}

/* Insert
 * PARAM:Value - value that will be inserted to the end of the calling object's array
 * POST:
 * Special Case:A new array will be created to copy the old array in, when the calling object's maximum size is full.
 * Then,release the memory of the old array. Max size of the new array = 2 * calling object's maximum size
 * */
void Sequence::insert(double value){
    if (arrSize>=maxSize){
        maxSize = maxSize * 2;
        double* newArray = deepCopyArray(array,arrSize,maxSize);

        releaseArray(array);
        array = newArray;
    }
    array[arrSize] = value;
    ++arrSize;
};

/* Insert
 * PRE:The value of insertedSize MUST be the exact number of elements contained in first parameter(insertedArr)
 * PARAM:Array that will be inserted to the end of the calling object's array and its  size
 * POST:
 * Special Case:A new array will be created to copy the two arrays in, when the calling object's maximum size is not large enough.
 * Then,release the memory of the two old arrays.
 *  - Max size of the new array = max(calling object's max size, calling object's current size + inserted size).
 * */
void Sequence::insert(double insertedArr[],int insertedSize){
    if (insertedSize == 0){
        return;
    }else if(maxSize<arrSize+insertedSize){
        double* newArr = deepCopyArray(array,arrSize,0,insertedArr,insertedSize,copyBothArray);
        releaseArray(array);
        array = newArr;
    } else{
        for (int i = 0; i < insertedSize; i++) {
            array[arrSize+i] = insertedArr[i];
        }
    }
    arrSize = arrSize + insertedSize;
    maxSize = maxSize>=arrSize?maxSize:arrSize;
    releaseArray(insertedArr);
};

/* Find
 * PARAM:The target which should be searched in the sequence.
 * POST: Return the number of sequence elements whose value is equal to the target.
 * */
int Sequence::find(double target) const {
    int count = 0;
    for (int i = 0; i < arrSize; i++) {
        if (array[i] == target){
            count++;
        }
    }
    return count;
}

/* Size
 * POST: Return the number of values in the calling object.
 * */
int Sequence::size() const{
    return arrSize;
}

/* Sum
 * POST: Return the sum of the values in the calling objects.
 * */
double Sequence::sum() const {
   return sum(array,arrSize);
}

/* Mean
 * POST: Return the average of the values in the calling object.
 * */
double Sequence::mean() const {
    if (arrSize==0){
        return 0;
    } else{
        return sum(array,arrSize)/arrSize;
    }
}

/* Median
 * POST: Returns the median of the values in the calling object.
 * */
double Sequence::median() const{
    if (arrSize == 0){
        return 0;
    } else{
        double* newArr = deepCopyArray(array,arrSize);

        sort(newArr,arrSize);
        double medianValue = 0;
        if (arrSize % 2 != 0) {
            medianValue = newArr[arrSize / 2];
        } else {
            medianValue = (newArr[arrSize / 2] + newArr[arrSize / 2 - 1]) / 2;
        }
        //release newArr - median function with a 'const' notation will not allow using releaseArray() function.
        delete [] newArr;
        newArr = nullptr;
        return medianValue;
    }
}

/* Standard Deviation
 * POST: Return the standard deviation of the values in the sequence.
 * */
double Sequence::stddev() const{
    if (arrSize == 0){
        return 0;
    } else{
        double meanValue = mean();
        //Create a new array to prevent modify the array in calling object
        double *diffSquareArray = deepCopyArray(array,arrSize);
        for (int i = 0; i < arrSize; i++) {
            //SD = root(sum(square(difference))/n)
            diffSquareArray[i] = pow(diffSquareArray[i] - meanValue, 2);
        }
        double sumDiffSquare = sum(diffSquareArray,arrSize);
        double stddevValue   = sqrt(sumDiffSquare/arrSize);

        //release diffSquareArray
        delete [] diffSquareArray;
        diffSquareArray = nullptr;
        return stddevValue;
    }
}

/* Concatenate
 * PARAM:The sequence which will be concatenated to the calling object.
 * POST: Returns a Sequence object whose:
 * 1.Maximum Array Size = max(2,the number of values stored in it).
 * 2.Real Array Size = the number of values stored in it
 * 3.Array Content = Content of array in both calling object and sequence object in parameter.
 * */
Sequence Sequence::concatenate(const Sequence & sq) const{
    Sequence newSq;
    newSq.arrSize = arrSize + sq.arrSize;
    newSq.maxSize = 2>=newSq.arrSize?2:newSq.arrSize;
    if (newSq.array != nullptr){
        delete [] newSq.array;
    }
    newSq.array = deepCopyArray(array,arrSize,newSq.maxSize,sq.array,sq.arrSize,copyBothArray);
    return newSq;
}


/* * * Private Function * * */

/* Copy Sequence into Calling Object
 * POST: It replaces all the content of calling object with the content of the sequence object in the parameter
 * */
void Sequence::copySequence(const Sequence & sq){
    //Deep Copy
    maxSize = sq.maxSize;
    arrSize = sq.arrSize;
    if (array != nullptr){
        releaseArray(array);
    }
    array = deepCopyArray(sq.array,sq.arrSize);
}

/* Array Generator
 * [PRE]:Two Mode Here
 * 1.Type = CopyFirstArray(default): Simply deeply copy first array into the new array.
 * 2.Type = CopyBothArray: Deeply copy both two array into the new array
 * (firstArrSize + secondArrSize) is the minimum valid value(>0 -- MUST!) for this function.so if assigned,newArrSizeIfNeeded >= that[MUST!]
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
double * Sequence::deepCopyArray (const double *firstArr, int firstArrSize, int newArrSizeIfNeeded, const double *secondArr,int secondArrSize, arrayCopyType type) const {
    int maximumSize = (firstArrSize + secondArrSize) >= newArrSizeIfNeeded ? (firstArrSize + secondArrSize) : newArrSizeIfNeeded;
    //NOTE: If people enter empty array(s),I will not handle this special case
    //Because I don't know how to initial an array with a length of zero in C++
    if (maximumSize == 0){
        cout << "ALL EMPTY ARRAY(S) INPUT IS NOT ALLOW !" <<endl;
        return nullptr;
    }

    if (type == copyFirstArray || type == copyBothArray) {
        double *newArray = new double[maximumSize];
        if (type == copyFirstArray) {
            for (int i = 0; i < firstArrSize; i++) {
                newArray[i] = firstArr[i];
            }
        }else {
            for (int i = 0; i < firstArrSize; i++) {
                newArray[i] = firstArr[i];
            }
            for (int j = 0; j < secondArrSize; j++) {
                newArray[firstArrSize + j] = secondArr[j];
            }
        }
        return newArray;
    }else {
        //Note:The following is not doing the actual handling to the potential exception here but kind of a stub.
        cout << "ERROR TYPE INPUT!" <<endl;
        return nullptr;
    }
}


/* PARAM:The array pointer which was pointing to the memory area that will be release in this function.
 * POST:
 * 1.Release the memory allocated for the array which was pointed by arr pointer
 * 2.Make arr point to nullptr.
 * */
void Sequence::releaseArray(double* arr){
    delete [] arr;
    arr = nullptr;
}

/* Sort(Min to Max)
 * PRE: The value of arraySize MUST be the exact number of elements contained in first parameter(arr)
 * PARAM:The array whose elements should be sorted and its size.
 * POST: The order of the array's elements will be well-organised(min to max).
 * */
void Sequence::sort(double* arr, int arraySize) const
{
    for(int i = 0;i < arraySize;i++){
        //比较两个相邻的元素
        for(int j = 0;j < arraySize-i-1;j++){
            if(arr[j] > arr[j+1]){
                double temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/* Sum
 * PRE: The value of arraySize MUST be the exact number of elements contained in first parameter(arr)
 * PARAM:The array whose elements should be calculated and its size.
 * POST: Return the sum of the values in the calling objects.
 * */
double Sequence::sum(const double * arr, int arraySzie) const{
    double sum = 0;
    for (int i = 0; i < arraySzie; i++) {
        sum += arr[i];
    }
    return sum;
}
