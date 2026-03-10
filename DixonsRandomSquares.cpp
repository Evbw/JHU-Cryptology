#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    long long n = 347881;

    long long base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    long long base_size = 9;
    vector<long long> smooth_z;
    vector<long long> smooth_vals;
    vector<vector<long long>> smooth_exponents;

    for ( int z = 600; z <= 660; z++ ) {
        long long z2 = (z*z) % n;

        long long candidates[2] = {z2, z2 - n};

        for ( int c = 0; c < 2; c++ ) {
            long long val = candidates[c];
            long long temp = val;

            vector<long long> exponents(10, 0);

            if ( temp < 0 ) {       //This should handle the case of the negative exponent
                exponents[0] = 1;
                temp = -temp;
            }

            for ( int i = 0; i < base_size; i++ ) {
                while ( temp % base[i] == 0 ) {
                    temp /= base[i];
                    exponents[i + 1]++;
                }
            }

            if ( temp == 1) {
                smooth_z.push_back(z);
                smooth_vals.push_back(val);
                smooth_exponents.push_back(exponents);
                break;
            }
        }
    }

    long long num_smooth = smooth_z.size();

    for ( int a = 0; a < num_smooth; a++ ) {
        for ( int b = a + 1; b < num_smooth; b++ ) {
            for ( int c = b + 1; c < num_smooth; c++ ) {
                vector<long long> combined(10, 0);
                bool all_even = true;

                for ( long long i = 0; i < 10; i++ ) {
                    combined[i] = smooth_exponents[a][i] + smooth_exponents[b][i] + smooth_exponents[c][i];
                    if ( combined[i] % 2 != 0 ) {
                        all_even = false;
                        break;
                    }
                }
                if (!all_even) {
                    continue;
                }
                
                cout<<endl<<"Valid combination found: z = "<<smooth_z[a]<<", "<<smooth_z[b]<<", "<<smooth_z[c]<<endl;

                long long x = (smooth_z[a] * smooth_z[b]) % n;
                x = (x * smooth_z[c]) % n;

                long long y = 1;
                long long half_exp;
                for ( int i = 0; i < base_size; i++ ) {
                    half_exp = combined[i + 1] / 2;
                    for ( int j = 0; j < half_exp; j++ ) {
                        y = (y*base[i]) % n;
                    }
                }
                
                long long diff = (x - y % n + n) % n;
                long long sum = (x + y) % n;
                long long ga = diff;
                long long gb = n;
                long long t;
                while ( gb != 0 ) {
                    t = gb;
                    gb = ga % gb;
                    ga = t;
                }
                long long factor1 = ga;

                ga = sum;
                gb = n;

                while ( gb != 0 ) {
                    t = gb;
                    gb = ga % gb;
                    ga = t;
                }
                long long factor2 = ga;

                cout<<"gcd(x-y, n) = "<<factor1<<endl;
                cout<<"gcd(x+y, n) = "<<factor2<<endl;

                cout<<"n = "<<(factor1*factor2)<<" x = "<<factor1<<" y = "<<factor2<<endl;
                if ( n == (factor1*factor2)) {
                    break;
                }
            }
        }
    }
    return 0;
}