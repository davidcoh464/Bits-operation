# Bits-operation
 New method to sort array of integers by sorting the bits from MSB to LSB with
 better runtime than merge sort or quick sort.
 with two ways of multiply and divide using bits
 operations. The main compares the runtime against standard operations.
 The sort idea is to move all the numbers that 31st bit is on to the end
 the array and then sort again in separate with 30st bit and so on until the 1st bit.
 This binary sort is non-comparison sorts and stable with similar idea to radix sort 
 but with different implementation and only with bitwise operations
