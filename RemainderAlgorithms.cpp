/*  Computes a number based on prime modulo values
 *  See Chinese Remainder Theorem for proof of solution existence
 *
 *  Originally written 2016-06-16
 *  
 */

#include <iostream>
#include <time.h>

#include <string>
#include <sstream>

using namespace std;

int calcValue();
int loadPrimes();
int loadAValues();

unsigned long long testSpeed();
unsigned long long testSpeed2();

unsigned long long n;
unsigned long long interval;
unsigned long long value;
unsigned long long a[15];
int mod[15];
int primeLimit = 15;
int prime[15];

clock_t timer;

string response;

int main() {
    loadPrimes();
    loadAValues();

    /*display a values
     for (int c = 0; c < primeLimit; c++)
     {
     cout << c << ": " << a[c] << endl;
     }
     */

    mod[0] = 1;
    mod[1] = 2;
    mod[2] = 2;
    mod[3] = 3;
    mod[4] = 1;
    mod[5] = 11;
    mod[6] = 13;
    mod[7] = 17;
    mod[8] = 19;
    mod[9] = 23;
    mod[10] = 29;
    mod[11] = 31;
    mod[12] = 37;
    mod[13] = 41;

    while (true) {
        cout << "Mods: ";
        getline(cin, response);
        stringstream(response) >> primeLimit;
        for (int c = 0; c < primeLimit; c++) //c max = number of mods
                {
            getline(cin, response);
            stringstream(response) >> mod[c];
        }

        timer = clock();
        calcValue();
        cout << value;
        timer = clock() - timer;
        cout << "     " << timer << "  " << CLOCKS_PER_SEC << endl;

        timer = clock();
        cout << testSpeed2();
        timer = clock() - timer;
        cout << "     " << timer << "  " << CLOCKS_PER_SEC << endl;

        cout << " (" << a[primeLimit - 1] << ")" << endl << endl;
        //cout << a[4] << endl; //a number = number of mods - 1
    }
    cin.get();
    return 0;
}

int calcValue() {
    int test = 0;

    if (mod[0] == 0)
        value = 0;
    else
        value = 1;
    int y;
    int x;
    for (int c = 1; c < primeLimit; c++) //c max = number of mods
            {
        y = (a[c] + mod[c] - value) % prime[c];
        x = a[c - 1] % prime[c];            //offset between prime mod and value
        while (true)    //calculate which iteration it is based on offsets
        {
            if (y % x == 0) {
                y = y / x;
                break;
            } else {
                y = y + prime[c];
                test = test + 1;
            }
        }

        cout << "(" << test << ") ";
        value = value + y * a[c - 1];
    }
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
    for (int c = 1; c < primeLimit; c++) {
        a[c] = a[c - 1] * prime[c];
    }
    return 0;
}

unsigned long long testSpeed() {
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

unsigned long long testSpeed2() {
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
        cout << "(" << test << ") ";
    }
    return value;

}
