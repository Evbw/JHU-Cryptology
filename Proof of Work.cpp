#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <openssl/evp.h>    //OpenSSL's envelope hashing API
using namespace std;

const int CHECKEDBYTES = 3;

string compute_digest(string algo_name, uint8_t* data, size_t length) {      //Helper function to compute hash digest
    const EVP_MD* algorithm = EVP_get_digestbyname(algo_name.c_str());
    
    EVP_MD_CTX* workspace = EVP_MD_CTX_new();

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_length = 0;

    EVP_DigestInit_ex(workspace, algorithm, nullptr);       //Initalize
    EVP_DigestUpdate(workspace, data, length);              //Feed data
    EVP_DigestFinal_ex(workspace, digest, &digest_length);  //Get result

    EVP_MD_CTX_free(workspace);

    ostringstream hex_builder;
    for ( unsigned int i = 0; i < digest_length; i++ ) {
        hex_builder << hex << setw(2) << setfill('0') << static_cast<int>(digest[i]);
    }

    return hex_builder.str();
}

bool has_leading_zeroes(const string& hex_string, int num_zero_bytes) {

    int chars_needed = num_zero_bytes * 2;

    for ( int i = 0; i < chars_needed; i++ ) {
        if ( hex_string[i] != '0') {
            return false;
        }
    }
    return true;
}

void search(string openssl_name, int input_bytes, int leading_zero_bytes) {

    uint64_t total_inputs = 1ULL << (input_bytes*8);    //For 3 bytes, 2^24 = 16777216 and needed an unsigned long long to handle a 64-bit number

    int count = 0;
    uint8_t buffer[8] = {};                             //Buffer to hold input bytes

    for ( uint64_t i = 0; i < total_inputs; i++ ) {

        for ( int b = 0; b < input_bytes; b++ ) {
            int shift_amount = (input_bytes - 1 - b) * 8;
            buffer[b] = static_cast<uint8_t>(i >> shift_amount) & 0xFF;
        }

        string digest = compute_digest(openssl_name, buffer, input_bytes);

        if ( has_leading_zeroes(digest, leading_zero_bytes) ) {

        }
    }
}

int main() {

    int input_bytes = CHECKEDBYTES;
    int leading_zero_bytes = CHECKEDBYTES;

    string SHA1 = "SHA1";
    string SHA512 = "SHA512";
    string SHA3512 = "SHA3-512";

    cout<<"Searching all "<<input_bytes<<"-byte strings for digests starting with "<<leading_zero_bytes<<" zero bytes";

    search(SHA1, input_bytes, leading_zero_bytes);
    search(SHA512, input_bytes, leading_zero_bytes);
    search(SHA3512, input_bytes, leading_zero_bytes);

    return 0;
}