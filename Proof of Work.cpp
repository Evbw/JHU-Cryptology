#include <iostream>
#include <openssl/evp.h>    //OpenSSL's envelope hashing API
using namespace std;

const int CHECKEDBYTES = 3;

void search(char* openssl_name, int input_bytes, int leading_zero_bytes) {
    
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