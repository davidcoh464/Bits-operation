#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <random>
#include "BitsOperation.h"
#include "BitsSort.h"
#include "StandardOperation.h"
#include "RegularSort.h"

using namespace std;
using namespace std::chrono;

#define CLOCK high_resolution_clock
const double ROUND_MULT = 10000;
const double ROUND_SORT = 10;
const double ROUND_DIV = 10000;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

int getRand();
int getRandWideRange();
void checkMult();
void checkSortArray();
void checkDiv();

int main()
{
    srand(time(nullptr));
    checkSortArray();
    checkMult();
    checkDiv();
    return 0;
}

void checkSortArray() {
    steady_clock::time_point start, stop;
    int countBinary = 0, countMerga = 0, countQuick = 0;
    BitsSort* sb = new BitsSort();
    RegularSort* sr = new RegularSort();
    for (int round = 0; round < ROUND_SORT;++round) {
        int size = rand();
        int* arr1 = new int[size];
        int* arr2 = new int[size];
        int* arr3 = new int[size];
        for (int i = 0;i < size;i++) {
            arr1[i] = arr2[i] = arr3[i] = getRandWideRange();
        }

        start = CLOCK::now();
        sb->binarySort(arr1, size);
        stop = CLOCK::now();
        countBinary += duration_cast<milliseconds>(stop - start).count();

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
            assert(arr1[i] == arr2[i] && arr1[i] == arr3[i]);
        }
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
    }
    cout << "Avarage time for one sort in milliseconds:\n";
    cout << "Binary sort: " << countBinary / ROUND_SORT << endl;
    cout << "Merga sort:  " << countMerga / ROUND_SORT << endl;
    cout << "Quick sort:  " << countQuick / ROUND_SORT << endl << endl;
}

void checkMult() {
    int a, b, resultMsb, resultAdd, resultStd, resultLsb;
    steady_clock::time_point start, stop;
    int countAdd = 0, countStd = 0, countMsb = 0, countLsb = 0;
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
        countAdd += duration_cast<nanoseconds>(stop - start).count();

        start = CLOCK::now();
        resultMsb = BitsOperation().multByMsb(a, b);
        stop = CLOCK::now();
        countMsb += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultLsb = BitsOperation().multByLsb(a, b);
        stop = CLOCK::now();
        countLsb += duration_cast<microseconds>(stop - start).count();

        assert(resultStd == resultMsb && resultStd == resultLsb && resultStd == resultAdd);
    }
    cout << "Avarage time for one multiplication in microseconds:\n";
    cout << "Standard multiply:    " << countStd / ROUND_MULT << endl;
    cout << "Bits multiply by lsb: " << countLsb / ROUND_MULT << endl;
    cout << "Bits multiply by msb: " << countMsb / ROUND_MULT << endl;
    cout << "Multiply by adding:   " << countAdd / ROUND_MULT << endl << endl;
}
void checkDiv() {
    int a, b, resultWay1, resultWay2, resultSub, resultStd;
    steady_clock::time_point start, stop;
    int countWay1 = 0, countWay2 = 0, countStd = 0, countSub = 0;
    for (int i = 0;i < ROUND_DIV;++i) {
        a = getRandWideRange();
        b = getRand();
        if (b == 0)
            continue;

        start = CLOCK::now();
        resultStd = StandardOperation().divStd(a, b);
        stop = CLOCK::now();
        countStd += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultSub = StandardOperation().divideBySubtraction(a, b);
        stop = CLOCK::now();
        countSub += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultWay1 = BitsOperation().divideWay1(a, b);
        stop = CLOCK::now();
        countWay1 += duration_cast<microseconds>(stop - start).count();

        start = CLOCK::now();
        resultWay2 = BitsOperation().divideWay2(a, b);
        stop = CLOCK::now();
        countWay2 += duration_cast<microseconds>(stop - start).count();

        assert(resultStd == resultSub);
        assert(resultStd == resultWay2);
        assert(resultStd == resultWay1);
    }
    cout << "Avarage time for one division in microseconds:\n";
    cout << "Standard division:       " << countStd / ROUND_DIV << endl;
    cout << "Bits division way 1:     " << countWay1 / ROUND_DIV << endl;
    cout << "Bits division way 2:     " << countWay2 / ROUND_DIV << endl;
    cout << "Division by subtraction: " << countSub / ROUND_DIV << endl;
}

int getRandWideRange() {
    return dist(rng);
}
int getRand() {
    return rand() % 3 ? rand() : -rand();
}

