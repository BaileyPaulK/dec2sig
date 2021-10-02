#include <math.h>

int largedtPow2 (double dec){
    return  floor( log(dec) / log(2) );
}

bool dec2AN (double dec, int array [], int size){
    if (dec != 0) {
        int power = largedtPow2 (dec);
        array[0] = power;
        for (int i = 1; i < size; i++) {
            if (dec / pow(2.0, power - (i-1) ) >= 1){
                dec -= pow(2.0, power - (i-1) );
                array[i] = 1;
            }
            else {
                array[i] = 0;
            }
            
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            array[i] = 0;
        }
    }
    return (dec != 0);
}

bool round (int array [], int size) {
    int i = size -1;
    if (array[i] == 1) { 
        while (array[i] == 1 && i >= 0) {
            array[i] = 0;
            i--;
        }
        if (i < 0) {
            return false;
        }
        else {
            array[i] = 1;
            return true;
        }
    }
    return true;
}

// int * Dec2A (double dec){
//     int power = largedtPow2 (dec);
//     int size = power + 2;
//     int array[size];
//     array[0] = size;
//     for (power; power >= 0; power--) {
//         if (dec / pow(2.0, power) >= 1){
//             dec -= pow(2.0, power);
//             array[size - power] = 1;
//         }
//         else {
//             array[size - power] = 0;
//         }
//     }
//     return array;
// }
