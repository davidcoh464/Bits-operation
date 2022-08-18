#pragma once
#include<iostream>
using namespace std;

static class BitsOperation {
public:
    /*
     * The first loop Multiply num2 n times in 2 until num2 > num1 
     * In the end of the loop temp equal to 2^n and num2 equal to the orignal num2 times temp(=2^n)
     * The second loop each time divide num2 and temp by 2, and if num1 is greater than or equal to num2 
     * it means that the orignal num2 enters at least 'temp' times in num1 so we can reduce num2(=temp*orignal num2) 
     * from num1 and add temp to the resulte 
    */
    int divisionWay1(long num1, long num2) {
        if (num1 == INT_MIN && num2 == -1) return INT_MAX;
        if (num1 == INT_MIN && num2 == 1) return INT_MIN;

        int ans = 0;
        long temp = 1;
        bool sing = true;

        if (num1 & 0x80000000)
        {
            sing = !sing;
            num1 = ~num1 + 1;
        }
        if (num2 & 0x80000000)
        {
            sing = !sing;
            num2 = ~num2 + 1;
        }
        // Multiples num2 and temp by 2 until num2 greater from num1
        while (num1 >= num2) {
            num2 = num2 << 1;
            temp = temp << 1;
        }
        // Divides num2 and temp by 2 until temp small or equals 1
        while (temp > 1) {
            num2 = num2 >> 1;
            temp = temp >> 1;
            // Each time that num1 is greater than num2 subtract num2 from num1 and add temp to the answer
            if (num1 >= num2)
            {
                num1 -= num2;
                ans += temp;
            }
        }
        return  sing ? ans : -ans;
    }

    /*
     *  num1/num2 = (num1/(num2*2^n)) * 2^n . 
     *  In the inner loop we multiply num2 in 2 until its multiply greater than num1
     *  That means that num1/num2 = ((num1 - (2^n * num2))/num2) + 2^n 
     *  So after the inner loop we add to the answer 2^n (=tempAns) and remove 2^n * num2 (=temp) from num1
     *  Then we recalculates the new num1 divided in num2 until num1 < num2
    */
    int divisionWay2(long num1, long num2) {
        if (num1 == INT_MIN && num2 == -1) return INT_MAX;
        if (num1 == INT_MIN && num2 == 1) return INT_MIN;
        
        bool sing = true;
        int ans = 0;

        if (num1 & 0x80000000)
        {
            sing = !sing;
            num1 = ~num1 + 1;
        }
        if (num2 & 0x80000000)
        {
            sing = !sing;
            num2 = ~num2 + 1;
        }
        
        while (num1 >= num2) {
            int temp = num2;
            int tempAns = 1;
            while (temp <= num1) {
                temp = temp << 1;
                tempAns = tempAns << 1;
            }
            temp = temp >> 1;
            tempAns = tempAns >> 1;
            num1 -= temp;
            ans += tempAns;
        }
        return  sing ? ans : -ans;
    }
    /*
     * This algorithm is based on num1*num2 = (num1*2)*(num2/2), if num2 is even
     * And num1*num2 = (num1*2)*(num2/2) + num1, if num2 is odd
     * So we multiply num1 in 2 and divide num2 in 2 until num2 equal to zero
     * And adds num1 to the answer each time that num2 is odd
    */
    int bitsMultByLsb(int num1, int num2)
    {
        int ans = 0;
        bool sing = true;
        if (num1 & 0x80000000)
        {
            sing = !sing;
            num1 = ~num1 + 1;
        }
        if (num2 & 0x80000000)
        {
            sing = !sing;
            num2 = ~num2 + 1;
        }
        if (num2 > num1)
            swap(num1, num2);

        while (num2)
        {
            if (num2 & 1) // If num2 is odd
                ans += num1;
            num1 = num1 << 1; // (num1*2)
            num2 = num2 >> 1; // (num2/2)
        }
        return  sing ? ans : -ans;
    }
    /*
     * This algorithm is base on that num1 * num2 = num1 *(2^log(num2)) + num1 *(num2 - (2^log(num2)))
     * So we add num1 *(2^log(num2)) to answer and then calculate num1 *(num2 - (2^log(num2)))
     * Until num2 equal to zero.
     * To find log(num2) in base of 2 we can just find the msb of num2
     * num1 *(2^log(num2)) = num1 shift left log(num2) = num1 << log(num2)
    */
    int bitsMultByMsb(int num1, int num2)
    {
        int ans = 0;
        bool sing = true;
        if (num1 & 0x80000000)
        {
            sing = !sing;
            num1 = ~num1 + 1;
        }
        if (num2 & 0x80000000)
        {
            sing = !sing;
            num2 = ~num2 + 1;
        }
        if (num2 > num1)
            swap(num1, num2);
        
        int msb = findMsbPlace(num2, 30);
        while (num2) {
            ans += (num1 << msb); // add num1 *(2^log(num2)) 
            num2 = num2 - (1 << msb); // remove msb from num2
            msb = findMsbPlace(num2, msb - 1);
        }
        return  sing ? ans : -ans;
    }

    bool greaterThan(int num1, int num2) {
        if (num1 & 0x80000000) { // If num1 is negative
            if (num2 & 0x80000000) // num1 negative and num2 negative 
                return greaterPostives(num1, num2);
            return false; // num1 negative and num2 non negative 
        }
        if (num2 & 0x80000000) // num1 non negative and num2 negative
            return true;
        return greaterPostives(num1, num2); // If num1 and num2 are non negative
    }

    bool greaterOrEqual(int num1, int num2) {
        if (num1 & 0x80000000) { // If num1 is negative
            if (num2 & 0x80000000) // num1 negative and num2 negative 
                return greaterOrEqualPostives(num1, num2);
            return false; // num1 negative and num2 non negative 
        }
        if (num2 & 0x80000000) // num1 non negative and num2 negative
            return true;
        return greaterOrEqualPostives(num1, num2); // If num1 and num2 are non negative
    }

private:
    /*
      * Finds the first bit that is on from 'place' bit to zero
      * return the msb place
     */
    int findMsbPlace(int n, int place) {
        int count = 1 << place;
        while (place > 0) {
            if (n & count)
                return place;
            --place;
            count = count >> 1;
        }
        return 0;
    }
    /*
     * Count the shift right of n until is zero
     * return the msb place
    */
    int findMsbPlace(int n)
    {
        int msb = 0;
        while (n >>= 1) {
            msb++;
        }
        return msb;
    }

    bool greaterPostives(int num1, int num2) {
        int count = 0x40000000;
        while(count) {
            if (num1 & count) {
                if (!(num2 & count))
                    return true;
            }
            else if (num2 & count)
                return false;
            count = count >> 1;
        }
        return false;
    }

    bool greaterOrEqualPostives(int num1, int num2) {
        int count = 0x40000000;
        while (count) {
            if (num1 & count) {
                if (!(num2 & count))
                    return true;
            }
            else if (num2 & count)
                return false;
            count = count >> 1;
        }
        return true;
    }

    bool smallerPostives(int num1, int num2) {
        return !greaterOrEqualPostives(num1, num2);
    }
    bool smallerOrEqualPostives(int num1, int num2) {
        return !greaterPostives(num1, num2);
    }

};