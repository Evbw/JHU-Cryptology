import math

def factor_over_base(value, base):
    powers = []
    temp = value
    for b in base:
        count = 0
        while temp % b == 0:
            count += 1
            temp //= b
        powers.append(count)
    if temp == 1:                   #Fully factored
        return powers
    return None                     #Anything leftover after factoring

def main():

    p = 227
    n = p-1
    alpha = 2                       #Order of Z_p^* = 226

    exponents = [32, 40, 59, 156]   #Given exponents
    relations = []                  #will hold (exponent, [2, 3, 5, 7, 11])

    factor_base = [2, 3, 5, 7, 11]

    for k in exponents:
        val = pow(alpha, k, p)
        exps = factor_over_base(val, factor_base)

if __name__ == "__main__":
    main()