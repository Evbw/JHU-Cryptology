#include <iostream>
#include <cstdint>
#include <openssl/evp.h>    //OpenSSL's envelope hashing API
using namespace std;

const int CHECKEDBYTES = 3;

void search(char* openssl_name, int input_bytes, int leading_zero_bytes) {

    uint64_t total_inputs = 1ULL << (input_bytes*8);    //For 3 bytes, 2^24 = 16777216 and needed an unsigned long long to handle a 64-bit number

    int count = 0;
    uint8_t buffer[8] = {};                             //Buffer to hold input bytes

    for ( uint64_t i = 0; i < total_inputs; i++ ) {

        for ( int b = 0; b < input_bytes; b++ ) {
            int shift_amount = (input_bytes - 1 - b) * 8;
            buffer[b] = static_cast<uint8_t>(i >> shift_amount) & 0xFF;
        }
    }
}

int main() {

    int input_bytes = CHECKEDBYTES;
    int leading_zero_bytes = CHECKEDBYTES;

    cout<<"Searching all "<<input_bytes<<"-byte strings for digests starting with "<<leading_zero_bytes<<" zero bytes";

    search("SHA1", input_bytes, leading_zero_bytes);
    search("SHA512", input_bytes, leading_zero_bytes);
    search("SHA3-512", input_bytes, leading_zero_bytes);

    return 0;
}