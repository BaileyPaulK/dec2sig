#include <iostream>
#include <stdio.h>
#include "binary.cpp"
using namespace std;

void printArray (int array [], int size, int from = 0, int to = 9999999) {
    cout << endl;
    for (int i = from; i < size && i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main () {
    int size = 10;
    int array [size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    printArray (array, size);
    round (array, size);
    printArray (array, size);
}