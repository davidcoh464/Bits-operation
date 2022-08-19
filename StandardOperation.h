#pragma once
#include<iostream>
using namespace std;

static class StandardOperation {
public:
	long int multStd(long num1, long num2) {
		return num1 * num2;
	}
	int divStd(int a, int b) {
		return a / b; 
	}
	long int multByAdding(long num1, long num2) {

		if (!num1 || !num2)
			return 0;

		bool sing = true;
		if (num1 < 0)
		{
			sing = !sing;
			num1 = -num1;
		}
		if (num2 < 0)
		{
			sing = !sing;
			num2 = -num2;
		}

		if (num1 < num2)
			swap(num1, num2);

		long ans = num1;
		while (num2 > 1) {
			ans += num1;
			--num2;
		}
		return  sing ? ans : -ans;
	}
	int divideBySubtraction(int num1, int num2) {
		if (num1 == INT_MIN && num2 == -1) return INT_MAX;
		if (num1 == INT_MIN && num2 == 1) return INT_MIN;

		bool sing = true;
		int count = 0;

		if (num1 < 0)
		{
			sing = !sing;
			num1 = -num1;
		}
		if (num2 < 0)
		{
			sing = !sing;
			num2 = -num2;
		}

		while (num1 >= num2) {
			num1 -= num2;
			++count;
		}
		return  sing ? count : -count;
	}

};
