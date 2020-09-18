//
// Created by tanny on 5/23/2020.
//
#pragma once
#include <iostream>
using std::cout;
using std::endl;
/* Parameters:
 * 1. array:  from which values are to be removed
 * 2. size:   the number of values stored in the array
 *            should set to the real number remained after removal
 * 3. value_to_be_removed:  value to be removed from the array
 *
 * Return value:
 * [int] the number of values that were removed
 *
 * Note:
 * assume that: 0 <= array size parameter <= size of array(NO handling for incompatible condition!)
*/
int remove(int *array, int &size, int value_to_be_moved){
    //1.if put in invalid size parameter, then NOT do removal operation
    // ** [Omitted, NOT Required in this Assignment]

    //2.receive all valid parameters
    int number_of_values_removed = 0;
    for(int i = 0; i < size; i++){
        if (array[i] == value_to_be_moved){
            //2.1 move forward 1 index and overwrite the value of current index
            for (int j = i; j < size - 1; j++){
                array[j] = array[j+1];
            }
            //2.2 change size
            -- size;

            //2.3 change iterator to the current index
            -- i;

            //2.4
            ++ number_of_values_removed;
        }
    }
    return number_of_values_removed;
}