#include <iostream>
#include <stdio.h>
#include "binary.cpp"
using namespace std;

void unnormalize(int array [], int size) {
    if (array[0] >= size - 1) {
        cout << "x's represent out of scope bits" << endl;
    }
    if (array[0] < 0) { 
        cout << "0.";
        int i = -1;
        while (i > array[0]) {
            cout << "0";
            i -= 1;
        }
    }
    int p = array[0];
    for (int i = 1; i < size; i++) {
        if (p == -1) {
            cout << ".";
        }
        cout << array[i];
        p -= 1;
    }
    while (p >= 0) {
        cout << "x";
        p -= 1;
    }
    cout << endl;
}

void prettyNormalized(int array [], int size) {
    cout << array[1] << ".";
    for (int i = 2; i < size; i++) {
        cout << array[i];
    }
    cout << " * 10^(" << array[0] << ")" << endl;
}

int main(){
    int sigBits = 4; //number of bits for the signifacant
    int sigSize = sigBits + 3; //power of 1rst, droped leading 1, extra bit to round
    int expBits = 3; //number of bits for the exponent
    int expSize = expBits + 1; //size the array must be (min + 1 for the power in array[o] of array[1])

    //bool sig [sigBits];
    int exp [expSize]; //+1 because first cell is the power of the 2nd cell
    int output [1 + sigBits + expBits];
    bool sign = 0;
    bool overFlow;
    int binary [sigSize]; //+3 1 is power, 1 for the droped leading 1, 1 for rounding
    int *t; 

    double dec;
    cout << "exponent bits = " << expBits << ". significant bits = " << sigBits << endl;
    cout << endl << "please input a number: ";
    cin >> dec;//input dec
    if (dec < 0) {
        sign = 1;
        dec *= -1;
    }
    overFlow = dec2AN(dec, binary, sigSize);//convert to binary in array zeroth (0) spot in array is n in 2^n for the value of the first placeint Largest2Divs (double dec)
    if (overFlow) {
        cout << "*information lost due to size of significant, be aware that the output will not equal the input if converted back" << endl;
    }
    // for (int i = 0; i < sigSize; i++){  //debug binary
    //     //printf( binary[i] );
    //     cout << binary[i] << " ";
    // }
    // cout << endl;
    int shift = pow(2,(expBits - 1)) - 1;
    overFlow = dec2AN(binary[0] + shift, exp, expSize); //pow(2,(expBits - 1)) - 1 shift for exponent. so for 3 bits it would be shift 3
    if (overFlow) {
        cout << "*note that there is an overflow in the exponent (even before the shift), this indicates that the input is waaaaaaaaaaaaaaay out of range" << endl;
    }
    // for (int i = 0; i < expSize; i++){  //debug exponent
    //     cout << exp[i] << " ";
    // }
    // cout << endl;

    //pretty display stuff for points
    cout << endl << "binary input" << endl;
    unnormalize(binary, sigSize);
    cout << endl << "normalized" << endl;
    prettyNormalized(binary, sigSize);
    cout << endl << "rounded" << endl;
    round(binary, sigSize);
    prettyNormalized(binary, sigSize);
    cout << endl << "but remember we drop the leading '1.' so what will be int the signifacant is" << endl;
    for (int i = 2; i < sigSize; i++) {
        cout << binary[i];
    }
    cout << endl << endl << "since the number of exponent bits = " << expBits << " then the shift on the exponent (" << binary[0] << ") is + " << shift << endl;
    cout << binary[0] << " + " << shift  << " = " << binary[0] + shift << ". which in binary";
    if (binary[0] + shift < 0) {
        cout << " is unfortinatly negative" << endl << "please note that this indicates that the number is out of range (specifically underflow) and will not convert properly" << endl;
    }
    else {
        cout << endl;
        unnormalize(exp, expSize);
    }
    //cout << endl << "normalized" << endl;
    //prettyNormalized(exp, expSize);
    if (sign == 1){
        cout << endl << "input was negative so sign bit is 1" << endl << endl;
    }
    else {
        cout << endl << "input was positive so sign bit is 0" << endl << endl;
    }


    output[0] = sign;
    if ((exp[0] > expBits - 1) || (exp[0] < 0)) {
        cout << "ERROR EXPONENT OVERFLOW" << endl << "the output will not be correct as the input is out of range" << endl;
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
    cout << endl << "output" << endl << "note read the above notes as even if out of range the output is still shown" << endl;
    for(int i = 0; i < 1 + expBits + sigBits; i++) {
        if ((i == 1) || (i == 1 + expBits)) {
            cout << " ";
        }
        cout << output[i];
    }
    cout << endl;

}