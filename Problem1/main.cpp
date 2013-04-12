/* 
 * File:   main.cpp
 * Author: Gokul
 *
 * Created on April 12, 2013, 12:58 AM
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>
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
    for (long long i = 2; i < (n/2); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void Prob3()
{
    //Problem: Find the largest prime factor of a given number
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
                    maxprime = i;
                    psuedochk /= i;
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

int main(int argc, char** argv) {
    Prob1();
    Prob2();
    Prob3();
    return 0;
}

