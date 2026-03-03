#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <openssl/evp.h>    //OpenSSL's envelope hashing API
using namespace std;

const int CHECKEDBYTES = 4;
const int MAXSUFFIXLENGTH = 8;

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

void search(string openssl_name, string& message, int leading_zero_bytes) {

    uint8_t buffer[256] = {};                             //Buffer to hold input bytes

    for ( int suffix_length = 1; suffix_length < MAXSUFFIXLENGTH; suffix_length++ ) {

        uint64_t total = 1ULL << (suffix_length * 8 );
        
        for ( uint64_t i = 0; i < total; i++ ) {
            for ( int b = 0; b < suffix_length; b++ ) {
                int shift_amount = (suffix_length - 1 - b) * 8;
                buffer[message.size() + b] = static_cast<uint8_t>(i >> shift_amount) & 0xFF;
            }
            string digest = compute_digest(openssl_name, buffer, message.size() + suffix_length);
            if ( has_leading_zeroes(digest, leading_zero_bytes) ) {
                cout<<endl<<"Found: "<<endl;
                cout<<"Suffix ("<<suffix_length<<" bytes):";
                for ( int b = 0; b < suffix_length; b++ ) {
                    cout<<hex<<setw(2)<<setfill('0')<<static_cast<int>(buffer[message.size() + b]);
                }
                cout<<endl<<"Full input: "<<message<<endl;
                for ( int b = 0; b < suffix_length; b++ ) {
                    cout<<hex<<setw(2)<<setfill('0')<<static_cast<int>(buffer[message.size() + b]);
                }
                cout<<endl<<"Digest: "<<digest<<endl;
                return;
            }
         }
        }
}

int main() {

    string section = "JHU695641";
    string SHA3512 = "SHA3-512";
    int leading_zero_bytes = CHECKEDBYTES;

    cout<<"Searching for shortest byte to append to \""<<section<<"\" so SHA3-512 starts with 00000000:";

    search(SHA3512, section, leading_zero_bytes);

    cout<<"Done."<<endl;
    return 0;
}