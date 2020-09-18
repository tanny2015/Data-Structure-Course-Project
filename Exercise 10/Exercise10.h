//
// Created by tanny on 7/19/2020.
//
#pragma once

#include <vector>
#include <string>


/* Sort the strings in a vector using the radix sort algorithm
 * PRE:   1. All the strings in the vector parameter are of the same length, which is equal to the length parameter
 *        2. All the strings in the vector parameter are composed only of lowercase letters
 * PARAM: 1. A string vector reference - The strings which needs to be ordered
 *        2. An integer value - The length of the strings
 * POST:  The strings in the vector are ordered by ASCII values(smallest to largest)
 * */

void radixsort(std::vector<std::string> &str, int strlength){
    //index 0 refers to a< ASCII:97>, so offset = 97
    int offset = 97;
    int vectorSize = str.size();
    int asciiRangeLength = 26;
    std::vector<std::vector<std::string>>bucket(asciiRangeLength);
    //go through the (charIndex)th character of each string, start from the rightmost
    for (int charIndex = strlength - 1; charIndex >= 0; charIndex--){
        for (int strIndex = 0; strIndex < vectorSize; strIndex++) {
            std::string currentStr = str[strIndex];

            //put the strings into specific position of the bucket, according to its (charIndex)th char value
            char item = currentStr[charIndex];
            std::vector<std::string> &innerItems = bucket[item - offset];
            innerItems.push_back(currentStr);
        }
        //use original vector<string> container to collect items in new order
        str.clear();
        //go through 26 vectors one by one
        for (int outerStrIndex = 0; outerStrIndex < asciiRangeLength; ++outerStrIndex) {
            std::vector<std::string>&innerItems = bucket[outerStrIndex];

            //when go into a specific vector, will collect all of items in it (from 1st index to the last)
            int innerItemsSize = innerItems.size();
            for (int innerStrIndex = 0; innerStrIndex < innerItemsSize; ++innerStrIndex) {
                std::string currentInnerStr = innerItems[innerStrIndex];
                str.push_back(currentInnerStr);
            }
        }
        bucket.clear();
        bucket.resize(asciiRangeLength);
    }
}
