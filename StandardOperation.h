#pragma once
#include<iostream>
using namespace std;

static class StandardOperation {
public:
	long int multStd(long num1, long num2) {
		return num1 * num2;
	}
	int divStd(int a, int b) { return a / b; }
	long int multByAdding(long num1, long num2) {

		if (!num1 || !num2)
			return 0;

		int sing = 1;
		if (num1 < 0)
		{
			sing = -sing;
			num1 = -num1;
		}
		if (num2 < 0)
		{
			sing = -sing;
			num2 = -num2;
		}

		if (num1 < num2)
			swap(num1, num2);

		long ans = num1;
		while (num2 > 1) {
			ans += num1;
			--num2;
		}
		return  sing == 1 ? ans : -ans;
	}
};