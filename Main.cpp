#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include"BitsOperation.h"
#include"StandardOperation.h"
#include"SortByBits.h"
#include"RegularSort.h"
using namespace std;
using namespace std::chrono;

#define CLOCK high_resolution_clock
const double ROUND_MULT = 10000;
const double ROUND_SORT = 10;
const double ROUND_DIV = 10000;

long int getRand();
void checkMult();
void checkSortArray();
void checkDiv();

int main()
{
    srand(time(NULL));
    checkSortArray();
    checkMult();
    checkDiv();
    return 0;
}

void checkSortArray() {
    steady_clock::time_point start, stop;
    int countBit = 0, countMerga = 0, countQuick = 0;
    SortByBits* sb = new SortByBits();
    RegularSort* sr = new RegularSort();
    for (int round = 0; round < ROUND_SORT;++round) {
        int size = rand();
        int* arr1 = new int[size];
        int* arr2 = new int[size];
        int* arr3 = new int[size];
        for (int i = 0;i < size;i++) {
            arr1[i] = arr2[i] = arr3[i] = getRand();
        }


        start = CLOCK::now();
        sb->sortBits(arr1, size);
        stop = CLOCK::now();
        countBit += duration_cast<milliseconds>(stop - start).count();


        start = CLOCK::now();
        sr->mergeSort(arr2, 0, size - 1);
        stop = CLOCK::now();
        countMerga += duration_cast<milliseconds>(stop - start).count();


        start = CLOCK::now();
        sr->quickSort(arr3, 0, size - 1);
        stop = CLOCK::now();
        countQuick += duration_cast<milliseconds>(stop - start).count();

        for (int i = 0;i < size;++i)
        {
            assert(arr1[i] == arr2[i]);
        }
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
    }
    cout << "Avarage time for one sort in milliseconds:\n";
    cout << "Bits sort:   " << countBit / ROUND_SORT << endl;
    cout << "Merga sort:  " << countMerga / ROUND_SORT << endl;
    cout << "Quick sort:  " << countQuick / ROUND_SORT << endl << endl;
}

void checkMult() {
    int a, b, resultMsb, resultAdd, resultStd, resultLsb;
    steady_clock::time_point start, stop;
    int countAdd = 0, countMsb = 0, countStd = 0, countLsb = 0;
    for (int i = 0;i < ROUND_MULT;++i) {
        a = getRand();
        b = getRand();

        start = CLOCK::now();
        resultStd = StandardOperation().multStd(a, b);
        stop = CLOCK::now();
        countStd += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultAdd = StandardOperation().multByAdding(a, b);
        stop = CLOCK::now();
        countAdd += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultMsb = BitsOperation().bitsMultByMsb(a, b);
        stop = CLOCK::now();
        countMsb += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultLsb = BitsOperation().bitsMultByLsb(a, b);
        stop = CLOCK::now();
        countLsb += duration_cast<microseconds>(stop - start).count();

        assert(resultStd == resultMsb && resultStd == resultAdd && resultStd == resultLsb);
    }
    cout << "Avarage time for one multiplication in microseconds:\n";
    cout << "Standard multiply:    " << countStd / ROUND_MULT << endl;
    cout << "Bits multiply by lsb: " << countLsb / ROUND_MULT << endl;
    cout << "Bits multiply by msb: " << countMsb / ROUND_MULT << endl;
    cout << "Multiply by adding:   " << countAdd / ROUND_MULT << endl<<endl;
}
void checkDiv() {
    int a, b, resultWay1, resultWay2, resultStd;
    steady_clock::time_point start, stop;
    int countWay1 = 0, countWay2 = 0, countStd = 0;
    for (int i = 0;i < ROUND_DIV;++i) {
        a = getRand();
        b = getRand();
        if (b == 0)
            continue;

        start = CLOCK::now();
        resultStd = StandardOperation().divStd(a, b);
        stop = CLOCK::now();
        countStd += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultWay1 = BitsOperation().divisionWay1(a, b);
        stop = CLOCK::now();
        countWay1 += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultWay2 = BitsOperation().divisionWay2(a, b);
        stop = CLOCK::now();
        countWay2 += duration_cast<microseconds>(stop - start).count();

        assert(resultStd == resultWay1 && resultStd == resultWay2);
    }
    cout << "Avarage time for one division in microseconds:\n";
    cout << "Standard division:   " << countStd / ROUND_DIV << endl;
    cout << "Bits division way 1: " << countWay1 / ROUND_DIV << endl;
    cout << "Bits division way 2: " << countWay2 / ROUND_DIV << endl;
}

long int getRand() {
    return rand() - rand();
}

