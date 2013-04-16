/* 
 * File:   main.cpp
 * Author: Gokul
 *
 * Created on April 12, 2013, 12:58 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <math.h>

using namespace std;

/*
 * 
 */
vector<int> * fibn;

uint64_t Fib(int n)
{
    assert(n >= 0);
    if (n < 2)
        return 1;
    else if (fibn->size() > n)
        return fibn->at(n);
    else
    {
        return (Fib(n-2) + Fib(n-1));        
    }
}

void Prob2()
{
    //Problem Statement:
    /* Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:
       1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
       By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
     */
    //Optimization : E(n) = 4*E(n-1) + E(n-2)
    //The above relation allows us to calculate and save only the even Fib numbers
    fibn = new vector<int> ();
    assert(fibn != NULL);
    uint64_t evenFib = 0;
    int i = 0;
    while(1)
    {
        uint64_t val = Fib(i++);
        if (val < 4000000)
        {
            if (val % 2 == 0)
            {
                evenFib += val;
//                printf("\n%lld", val);
            }
        }
        else
            break;
        fibn->push_back(val);
    }
    printf("Prob2 Soln : Sum of Even Fib < 4M => %ld\n", evenFib);
}

void Prob1()
{
    //Problem Statement :
    /*If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
      Find the sum of all the multiples of 3 or 5 below 1000.*/
    //Optimization Tip : SumOf(Multiples of (3)) + SumOf (MultiplesOf(5)) - SumOf(MultiplesOf(15))
    //SumOf(MultipliesOf(n)) = n*(d(d+1))/2
    int sum = 0;
    int mult3 = 0, mult5 = 0, mult15 = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (i % 3 == 0)
            mult3 += i;
        if (i % 5 == 0)
            mult5 += i;
        if (i % 15 == 0)
            mult15 += i;
    }
    printf ("Prob1 Soln : Sum = %d\n", (mult3+mult5-mult15));
}

bool isPrime(long long n)
{
    if (n <= 2)
        return true;
    for (long long i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void Prob3()
{
    //Problem: Find the largest prime factor of a given number
    //Optimizations : remove pseduochk if possible! check only upto sqrt of number for prime or the number itself is prime
    long long num = 600851475143LL;
    long long psuedochk = num;
    long long maxprime = 2;
    while(1)
    {
        bool found = false;
        if (isPrime(psuedochk))
        {
            maxprime = (maxprime > psuedochk) ? maxprime : psuedochk;
            break;
        }
        for (long long i = maxprime; i < (psuedochk/2); i++)
        {
            if (isPrime(i))
            {
                if (psuedochk % i == 0)
                {
                    while (psuedochk % i == 0)
                    {
                        psuedochk /= i;
                    }
                    maxprime = i;
                    found = true;
                    //printf("Prime = %d; New No %d\n", i, psuedochk);
                    break;
                }
            }
        }
        if (!found)
            break;
    }
    printf("Prob3 Soln : Largest Prime Factor = %ld\n", maxprime);
}

bool isPalindrome (uint64_t num)
{
    ostringstream ss;
    ss << num;
    string s = ss.str();
    for (int i = 0; i < (s.length())/2; i++)
    {
        if (s.at(i) != s.at(s.length()-1-i))
            return false;
    }
    return true;
}

void Prob4()
{
    //Find the largest palindrome number made from product of two 3-digit numbers
    //9009 -> palindrome number
    //Optimization : The palindrome must be 6-digit at max (since < 999*1000); So 100000x + 10000y + 1000z + 100z + 10y + x = 100001x + 10010y + 110z -> divisible by 11
    //So either i or j should be divisible by 11
    int maxval = 999;
    uint64_t mval = 0;
    int dec = 1, sval = maxval;
    for (int i = maxval; i >= 100; i--)
    {
        if (i % 11 != 0)
        {
            dec = 11;
            sval = 990;
        }            
        else
        {
            dec = 1;
            sval = maxval;
        }
        
        for (int j = sval; j >= i; j = j - dec)
        {
            uint64_t val = i*j;
            if (isPalindrome(val))
            {
                if (mval < val)
                    mval = val;
                //printf("Val = %ld i = %d j = %d\n", val, in, j); //Some bug in printf code! Always prints i as 0
            }
        }
    }
    printf("Prob4 Soln : Largest Palindrome = %ld\n", mval);
}

//Just a placeholder to be used in future
vector<int> * returnPrimeFactors(int num)
{
    int pNum = num;
    vector<int> * vPrime = new vector<int>();
    for (int i = 2; i <= num; i++)
    {
        if (isPrime(i))
        {
            vPrime->push_back(0);
            while(pNum % i == 0)
            {
                (vPrime->at(vPrime->size()-1))++;
                pNum /= i;
            }
        }
    }
    return vPrime;
}

void Prob5()
{
    //Find LCM of numbers 1 to 20
    //Current idea is to find count of prime factors for each number from 1 to 20 and compare it with current counters and increment it if higher
    int maxNum = 20;
    vector<int> pNum;
    vector<int> pCnt;
    uint64_t lcm = 1;
    
    for (int i = 2; i <= maxNum; i++)
    {
        if (isPrime(i))
        {
            int cnt = (int) floor ((double)log(maxNum) / log(i));
            pCnt.push_back(cnt);
            pNum.push_back(i);
            //printf("Prime = %d Cnt = %d\n", i, cnt);
            lcm *= (uint64_t) pow(i, cnt);
        }
    }
    printf("Prob5 Soln : LCM is %lld\n", lcm);
}

void Prob6()
{
    //Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
    int maxNum = 100;
    uint64_t sqrOfSum = (uint64_t) pow(((maxNum)*(maxNum+1)/2), 2); // (n(n+1)/2)^2
    uint64_t sumOfSqr = (maxNum)*(2*maxNum + 1)*(maxNum + 1) / 6; //Formula = n*(2n+1)*(n+1)/6
    printf("Prob6 Soln : Diff is %lld\n", (sqrOfSum - sumOfSqr)); 
}

void Prob7()
{
    //If 1st prime number is 2, what is 10,001st prime number
    int matchCnt = 10001;
    int cnt = 1;
    uint64_t num = 3;
    while(1)
    {
        if (isPrime(num))
        {
            cnt++;
            if (cnt == matchCnt)
            {
                printf("Prob7 Soln : 10001st Prime = %lld\n", num);
                break;
            }
        }
        num += 2;
    }
}

void Prob8()
{
    
}

int main(int argc, char** argv) {
    Prob1();
    Prob2();
    Prob3();
    Prob4();
    Prob5();
    Prob6();
    Prob7();
    Prob8();
    return 0;
}

