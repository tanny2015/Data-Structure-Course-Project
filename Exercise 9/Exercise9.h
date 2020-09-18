//
// Created by tanny on 7/12/2020.
//

#pragma once

/* Tell if the elements of an array can construct a Min Heap
 * PARAM: 1.An integer array - The array which needs to be assessed whether it can construct a Min Heap
 *        2.An integer value - The number of occupied elements of the array
 * POST:  Return a bool value which indicates whether the elements of this array can construct a Min Heap.
 * */
bool isMinHeap(const int * array, int size){
    if (size < 2){
        return true;
    }
    for(int parentIndex = 0; parentIndex < size; ++ parentIndex){
        bool parentIsMin = true;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex= 2 * parentIndex + 2;
        if (leftChildIndex < size){
            if (rightChildIndex < size){
                parentIsMin = (array[parentIndex] <= array[leftChildIndex]) && (array[parentIndex] <= array[rightChildIndex]);
            }else{
                parentIsMin = (array[parentIndex] <= array[leftChildIndex]);
            }

            if (!parentIsMin){
                return false;
            }
        }
    }
    return true;
}


