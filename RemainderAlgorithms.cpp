/*  Computes a number based on prime modulo values
 *  See Chinese Remainder Theorem for proof of solution existence
 *  Implements and times three algorithms for computing the solution
 *
 *  Supports up to 15 primes
 *
 *  Originally written 2016-06-16
 *  Updated for Math290 Reading in Number Theory
 *  
 */

#include <iostream>
#include <time.h>

#include <string>
#include <sstream>

using namespace std;

int loadPrimes();
int loadAValues();

unsigned long long method1();
unsigned long long method2();
unsigned long long method3();

unsigned long long a[15];
int mod[15];
int prime[15];

clock_t timer;
string response;
int primeLimit;

int main() {
    loadPrimes();
    loadAValues(); //product of the first nth primes

    /*display a values
     for (int c = 0; c < 15; c++)
     {
        cout << c << ": " << a[c] << endl;
     }
     */

    while (true) {
        cout << "Mods: ";
        getline(cin, response);
        stringstream(response) >> primeLimit; //how many primes
        if (primeLimit > 15) {
            cout << "Supports up to 15 primes.\n";
            continue;
        }
        for (int c = 0; c < primeLimit; c++) {
            getline(cin, response);
            stringstream(response) >> mod[c];
        }
        cout << endl;

        timer = clock();
        cout << method1(); //brute force method
        timer = clock() - timer;
        cout << "     Time: " << timer << endl;
        
        timer = clock();
        cout << method2();
        timer = clock() - timer;
        cout << "     Time: " << timer << endl;
        
        timer = clock();
        cout << method3();
        timer = clock() - timer;
        cout << "     Time: " << timer << endl;
        
        cout << "(" << CLOCKS_PER_SEC << " clocks per second)" << endl;

        //print the number to add to generate more solutions
        cout << " (" << a[primeLimit - 1] << ")" << endl << endl;
    }
    cin.get();
    return 0;
}

int loadPrimes() {
    prime[0] = 2;
    prime[1] = 3;
    prime[2] = 5;
    prime[3] = 7;
    prime[4] = 11;
    prime[5] = 13;
    prime[6] = 17;
    prime[7] = 19;
    prime[8] = 23;
    prime[9] = 29;
    prime[10] = 31;
    prime[11] = 37;
    prime[12] = 41;
    prime[13] = 43;
    prime[14] = 47;
    return 0;
}

int loadAValues() {
    a[0] = 2;
    for (int c = 1; c < 15; c++) {
        a[c] = a[c - 1] * prime[c];
    }
    return 0;
}

/* Calculates the value by brute force */
unsigned long long method1() {
    unsigned long long n;
    for (n = 0; n < a[primeLimit - 1]; n++) {
        for (int n2 = 0; n2 < primeLimit; n2++) {
            if (n % prime[n2] != mod[n2])
                break;
            if (n2 == primeLimit - 1)
                return n;
        }
    }
    return 0;
}

/* Calculates the value by a second method */
unsigned long long method2() {
    unsigned long long value;
    
    //keeps track of how many times value had to be incremented
    int test = 0;
    
    if (mod[0] == 0)
        value = 0;
    else
        value = 1;
    for (int n = 1; n < primeLimit; n++) {
        while (value % prime[n] != mod[n]) {
            value = value + a[n - 1];
            test = test + 1;
        }
    }
    
    //print how many times test was incremented
    //cout << "(" << test << ") ";
    return value;
}

/* Calculates the value by a third method */
unsigned long long method3() {
    unsigned long long value;
    
    //keeps track of how many times value had to be incremented
    int test = 0;
    
    if (mod[0] == 0)
        value = 0;
    else
        value = 1;
    int y;
    int x;
    for (int c = 1; c < primeLimit; c++) {
        y = (a[c] + mod[c] - value) % prime[c];
        x = a[c - 1] % prime[c]; //offset between prime mod and value
        while (true) //calculate which iteration it is based on offsets
        {
            if (y % x == 0) {
                y = y / x;
                break;
            } else {
                y = y + prime[c];
                test = test + 1;
            }
        }

        //print how many times test was incremented
        //cout << "(" << test << ") ";
        value = value + y * a[c - 1];
    }
    return value;
}
