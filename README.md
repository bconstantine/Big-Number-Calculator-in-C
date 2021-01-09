# Big-Number-Calculator-in-C
A calculator that can calculate up to 30 digit integer and 30 digit floating point

One of the questions that was given by National Taiwan University Science of Technology (NTUST)'s Programming class. 

Question:
Large numbers are numbers that are significantly larger than those ordinarily used in everyday life, for instance in simple counting or in monetary transactions. The term typically refers to large positive integers, or more generally, large positive real numbers, but it may also used in other context. 
A simple way to deal with Large number is to split it into smaller numbers and then calculate each separate part. For example, if the input is 123456789, we ccan save each digiti in the array and then calculate each digit. The result should also be stored in an array, you do not need to transfer it to integer or floating point number. 
Make a calculator that can calculate ADDITION, SUBTRACTION, and MULTIPLICATION that can take input up to 30 digit integer and 30 digit floating point. 

Input:
Only add, minus, and multiply two large numbers (+ or - or *)
All inputs may be positive or negative numbers.
-A--B is possible
The number may contain a decimal point
The first input is how many testing data.

Output:
Print the correct result of the equation.
The answer you print should have its data number.

Example:
Input:
3
12345678991019231124+1234567890000000
987654.321--123.456789
1111.1111*2

Output:
#1:12346913558909231124
#2:987777.777789
#3:2222.2222
