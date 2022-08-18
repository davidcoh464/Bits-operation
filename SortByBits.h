#pragma once
#include<iostream>
using namespace std;

class SortByBits {
    void sortBits(int* arr, int start, int end, int bitOn) {
        if (end - start <= 0) // If the array has only one or less values
            return;
        if (bitOn == 0) // If we have already checked all the bits
            return;
        int replace = end;
        //Finds all numbers from the start that 'bitsOn' is 1 and move them to the end of the array
        for (int i = start;i <= end && i <= replace;++i) {
            if (arr[i] & bitOn)
            {
                while (arr[replace] & bitOn && replace > i)
                    --replace;
                swap(arr[i], arr[replace]);
                --replace;
            }
        }
        bitOn >>= 1;
        //Sorts all numbers from 'start' until 'replace' that 'bitOn' is 0
        sortBits(arr, start, replace, bitOn);
        //Sorts all numbers from 'replace + 1' until the 'end' that 'bitOn' is 1
        sortBits(arr, replace + 1, end, bitOn);
    }
public:
    void sortBits(int* arr, int size) {
        int endNeg = -1;
        // Moves all the negatives numbers to the start of the array
        for (int i = size - 1; i > 0 && i > endNeg;--i) {
            if (arr[i] & 0x80000000) { // If arr[i] is negative  
                endNeg++;
                while (arr[endNeg] & 0x80000000 && i > endNeg)
                    endNeg++;
                swap(arr[i], arr[endNeg]);
            }
        }
        //Sorting the negative numbers that are from place 0 until 'endNeg' place
        sortBits(arr, 0, endNeg, 0x40000000);
        //Sorting the non negative numbers that are from place 'endNeg' + 1 until the end
        sortBits(arr, endNeg + 1, size - 1, 0x40000000);
    }
};