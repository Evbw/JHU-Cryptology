#include <iostream>
using namespace std;

int xord(int mask, int val) {
    int bits = mask & val;
    int parity = 0;
    while (bits) {
        parity ^= (bits & 1);
        bits >>= 1;
    }
    return parity;
}

int main() {
    int sbox[16] = {0x7, 0x3, 0xA, 0x5, 0x4, 0x8, 0x9, 0x2, 0xE, 0x6, 0xC, 0x1, 0xD, 0xB, 0x0, 0xF};

    for ( int a = 0; a < 16; a++ ) {
        for ( int b = 0; b < 16; b++ ) {
            int count = 0;
            for ( int x = 0; x < 16; x++ ) {
                int y = sbox[x];
                int ax = xord(a, x);
            }
        }
    }

    return 0;
}