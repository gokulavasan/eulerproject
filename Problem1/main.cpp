/* 
 * File:   main.cpp
 * Author: Gokul
 *
 * Created on April 12, 2013, 12:58 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
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
    printf ("Sum = %d\n", (mult3+mult5-mult15));
    return 0;
}

