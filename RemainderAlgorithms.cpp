/*  Computes a number based on prime modulo values
 *  See Chinese Remainder Theorem for proof of solution existence
 *  Implements and times three algorithms for computing the solution
 *  In main(), use tests() to time algorithms for many values or oneTest() to check one number only
 *
 *  Supports up to 15 primes because the product of
 *  the first 16 primes would surpass 2^64 - 1, the size of an unsigned long long
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
void tests(int, unsigned long long, unsigned long long);
void oneTest();

unsigned long long a[15];
int mod[15];
int prime[15];

clock_t timer;
string response;
int primeLimit; //how many input modulos

int main() {
    loadPrimes();
    loadAValues(); //product of the first nth primes

    //inputs: how many modulos, minimum test value, maximum test value
    tests(15, a[14] - 10000000, a[14]);
    
    //oneTest();
    
    return 0;
}


/** Runs a test for a given number of mods and a range of inputs */
void tests(int modulos, unsigned long long min, unsigned long long max) {
    cout << "Running " << max-min+1 << " numers..." << endl;
    primeLimit = modulos;
    unsigned long long currTest = 0;
    for (int alg = 0; alg < 4; alg++) {
        //run timer while all possibilities checked because otherwise times are too fast
        timer = clock();
        //try all possibilities
        for (currTest = min; currTest <= max; currTest++) {
            //get the modulo values
            for (int i = 0; i < modulos; i++) {
                mod[i] = currTest % prime[i];
            }
            //alg == 0 is our control test just iterating from min to max
            /* method1() commented out because super slow
            if (alg == 1)
                //method1(); //brute force method
            */
            if (alg == 2)
                method2();
            if (alg == 3)
                method3();
        }
        timer = clock() - timer;
        cout << "Time for algorithm " << alg << ": " << timer << endl;
    }
    cout << "(" << CLOCKS_PER_SEC << " clocks per second)" << endl;
}

/** Runs a test for one input number */
void oneTest() {
    cout << "How many mods: ";
    getline(cin, response);
    stringstream(response) >> primeLimit; //how many primes
    if (primeLimit > 15) {
        cout << "Supports up to 15 primes.\n";
        return;
    }
    for (int c = 0; c < primeLimit; c++) {
        getline(cin, response);
        stringstream(response) >> mod[c];
    }
    cout << endl;

    timer = clock();
    //cout << method1(); //brute force method, commented out for now because super slow
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
