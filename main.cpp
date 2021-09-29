#include <iostream>
#include <stdio.h>
#include "binary.cpp"
using namespace std;

int main(){
    int sigBits = 4; //number of bits for the signifacant
    int expBits = 3; //number of bits for the exponent

    //bool sig [sigBits];
    int exp [expBits + 1]; //+1 because first cell is the power of the 2nd cell
    int output [1 + sigBits + expBits];
    bool sign = 0;
    bool overFlow;
    int binary [sigBits + 3]; //+3 1 is power, 1 for the droped leading 1, 1 for rounding
    int *t; 

    double dec;
    cout << "exponent bits = " << expBits << ". significant bits = " << sigBits << endl;
    cin >> dec;//input dec
    if (dec < 0) {
        sign = 1;
        dec *= -1;
    }
    overFlow = dec2AN(dec, binary, sigBits + 3);//convert to binary in array zeroth (0) spot in array is n in 2^n for the value of the first placeint Largest2Divs (double dec)
    
    for (int i = 0; i < sigBits + 3; i++){  //debug binary
        //printf( binary[i] );
        cout << binary[i] << " ";
    }
    cout << endl;
    
    overFlow = dec2AN(binary[0] + pow(2,(expBits - 1)) - 1, exp, expBits + 1); //pow(2,(expBits - 1)) - 1 shift for exponent. so for 3 bits it would be shift 3

    for (int i = 0; i < expBits + 1; i++){  //debug exponent
        cout << exp[i] << " ";
    }
    cout << endl;

    output[0] = sign;

    if ((exp[0] > expBits - 1) || (exp[0] < 0)) {
        cout << "ERROR OVERFLOW" << endl;
    }
    else{
        int power = exp[0];
        int p = 1;
        for (int i = 1; i <= expBits; i++) {
            if ((expBits - i) > power) {
                output[i] = 0;
            }
            else {
                output[i] = exp[p];
                p++;
            }
        }

        for (int i = 1; i <= sigBits; i++) {
            output[expBits + i] = binary[i + 1];
        }
    }

    for(int i = 0; i < 1 + expBits + sigBits; i++) {
        if ((i == 1) || (i == 1 + expBits)) {
            cout << " ";
        }
        cout << output[i];
    }
    cout << endl;

}