#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string to_string_128(unsigned __int128 val) {
    if ( val == 0 ) {
        return 0;
    }
    string s;
    while ( val > 0 ) {
        s = char('0' + val % 10) + s;
        val /= 10;
    }
    return s;
}

unsigned __int128 from_string_128(const string &s) {
    unsigned __int128 val = 0;
    for ( char c : s ) {
        val = val * 10 + (c - '0');
    }
    return val;
}

unsigned __int128 sam(unsigned __int128 c, unsigned __int128 x, unsigned __int128 n, unsigned __int128 z) {
    vector<int> bits;
    unsigned __int128 temp = x;

    while ( temp > 0 ) {
        bits.push_back(temp % 2);
        temp /= 2;
    }

    int l = bits.size();

    for ( int i = l - 1; i >= 0; i-- ) {
        z = z * z % n;
        if ( bits[i] == 1 ) {
            z = z * c % n;
        }
    }

    return z;
}

__int128 f(__int128 x, __int128 n) {
    return (x*x + 1) % n;
}

__int128 gcd_128(__int128 x, __int128 n) {
    while ( n != 0 ) {
        __int128 t = n;
        n = x % n;
        x = t;
    }
    return x;
}

__int128 pollard_rho(__int128 n, __int128 x1) {
    __int128 x = x1;
    __int128 xp = f(x, n);
    __int128 xdiff = x - xp;
    if ( xdiff < 0 ) {
        xdiff = -xdiff;
    }
    __int128 p = gcd_128(xdiff, n);

    while ( p == 1 ) {
        x = f(x, n);
        xp = f(xp, n);
        xp = f(xp, n);
        xdiff = x - xp;
        if ( xdiff < 0 ) {
            xdiff = -xdiff;
        }
        p = gcd_128(xdiff, n);
    }

    if ( p == n ) {
        return 0;
    }
    return p;
}

__int128 factor_n(__int128 n) {
    for ( __int128 x1 = 2; x1 < 100; x1++ ) {
        __int128 p = pollard_rho(n, x1);
        if (p != 0 && p != n) {
            return p;
        }
    }
    return 0;
}

__int128 eea(__int128 a, __int128 b, __int128 &s, __int128 &t) {

    __int128 a0 = a;
    __int128 b0 = b;
    __int128 t0 = 0;
    __int128 s0 = 1;
    __int128 q = a0/b0;
    __int128 r = a0-q*b0;

    __int128 temp;

    while ( r > 0 ) {
        temp = t0-q*t;
        t0 = t;
        t = temp;
        temp = s0-q*s;
        s0 = s;
        s = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0-q*b0;
    }
    r = b0;

    return r;
}

__int128 mod_inverse(__int128 totient, __int128 e) {
    __int128 t = 1;
    __int128 s = 0;
    __int128 gcd = eea(totient, e, s, t);

    if ( gcd != 1 ) {
        cout<<"Error: e = "<<to_string_128(e)<<" has no inverse modulo "<<to_string_128(totient)<<"."<<endl;
        return -1;
    }

    t = ((t%totient)+totient)%totient;
    return t;
}

__int128 encode_block(char c1, char c2, char c3) {
    int v1 = toupper(c1) - 'A';
    int v2 = toupper(c2) - 'A';
    int v3 = toupper(c3) - 'A';
    v1 *= 676;                          //676 = 26^2
    v2 *= 26;
    __int128 result = v1 + v2 + v3;
    return result;
}

string decode_block(__int128 value) {  //Decode base 26 number back into 3 letters
    string result = "   ";              //3 empty characters
    result[2] = 'A' + (value % 26);
    value /= 26;
    result[1] = 'A' + (value % 26);
    value /= 26;
    result[0] = 'A' + (value % 26);
    return result;
}

unsigned __int128 encrypt(unsigned __int128 m, unsigned __int128 e, unsigned __int128 n) {
    return sam(m, e, n, 1);
}

unsigned __int128 decrypt(unsigned __int128 c, unsigned __int128 d, unsigned __int128 n) {
    return sam(c, d, n, 1);
}

//Note that much of this code is refactored from an assignment I did as a team in Assembly for prerequisite class
//https://github.com/Evbw/RSATeam2/blob/master/RSA.s
int main() {

    __int128 n = 4790285247827309603;
    __int128 e = 65537;
    __int128 p, q;
    __int128 totient;

    cout<<endl<<"This is an program that uses a fixed public key to encode/decode using RSA."<<endl;
    cout<<"Given public key: (b, n) = ("<<to_string_128(e)<<", "<<to_string_128(n)<<")"<<endl;
    
    p = factor_n(n);
    q = n / p;
    totient = (p - 1)*(q - 1);
    
    __int128 d = mod_inverse(totient, e);
    if ( d == -1 ) {
        cout<<"Invalid value. Exiting."<<endl;
        return 1;
    }

    int choice = 0;
    while ( choice != -1 ) {
        cout<<"Choose an option:"<<endl;
        cout<<"1 - Encrypt a message (base-26 blocks)"<<endl;
        cout<<"2 - Decrypt a message (base-26 blocks)"<<endl;
        cout<<"3 - Decrypt from file (base-26 blocks)"<<endl;
        cout<<"-1 Exit"<<endl;
        cin>>choice;

        if ( choice == 1 ) {                                        //Encryption routine
            string message;
            cout<<"Enter a message (letters only)"<<endl;
            cin>>message;

            while ( message.length() % 3 != 0 ) {                   //Pad the message if necessary
                message += 'A';
            }

            vector<unsigned __int128>ciphertext;

            for ( int i = 0; i < static_cast<int>(message.length()); i += 3 ) {
                __int128 m = encode_block(message[i], message[i+1], message[i+2]);
                unsigned __int128 c = encrypt(m, e, n);
                ciphertext.push_back(c);
            }

            cout<<"Full ciphertext:"<<endl;
            for ( int i = 0; i < ciphertext.size(); i++ ) {
                cout<<to_string_128(ciphertext[i]);
                if ( i < ciphertext.size() - 1 ) {
                    cout<< " ";
                }
            }
            cout<<endl;
        }

        else if ( choice == 2 ) {                                  //Decryption routine 
            string plaintext = "";
            unsigned __int128 c;
            string c_str;
            cout<<"Please enter the ciphertext in blocks separated by a space. Enter a non-number when finished:"<<endl;
            while ( cin >> c_str ) {
                c = from_string_128(c_str);
                unsigned __int128 m = decrypt(c, d, n);
                string block = decode_block(m);
                plaintext += block;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Decrypted message:"<<plaintext<<endl;
        }

        else if ( choice == 3 ) {
            string filename;
            cout<<"Enter path to encrypted file:"<<endl;
            cin>>filename;

            ifstream infile(filename);
            while ( !infile.is_open()) {
                cout<<"Error reading file. Please reenter file path:"<<endl;
                cin>>filename;
            }

            string plaintext = "";
            string token;
            string block;
            __int128 c;
            __int128 m; 
            while ( infile >> token ) {
                c = from_string_128(token);
                m = decrypt(c, d, n);
                block = decode_block(m);
                plaintext += block;
            }
            infile.close();
            cout<<"Decrypted message: "<<plaintext<<endl;
        }

        if ( choice == 0 || choice > 3 || choice < -1 ) {
            cout<<"Invalid input. Please try again"<<endl;
            continue;
        }

    }

    return 0;
}