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

    #Part a

    exponents = [32, 40, 59, 156]   #Given exponents
    relations = []                  #will hold (exponent, [2, 3, 5, 7, 11])

    factor_base = [2, 3, 5, 7, 11]

    print("Part A")
    print("")

    for k in exponents:
        val = pow(alpha, k, p)
        exps = factor_over_base(val, factor_base)
        if exps is not None:
            relations.append((k, exps))
            pieces = []
            for b,e in zip(factor_base, exps):
                if e > 0:
                    if e > 1:
                        pieces.append(f"{b}^{e}")
                    else:
                        pieces.append(str(b))
            print(f"2^{k} mod {p} = {val} = {' '.join(pieces)}")

    print("")
    print("Part B")
    print("")
    #Part b

    L = {2: 1}
    L[11] = (32-4*L[2]) % n
    L[5] = (40-1*L[2]-L[11]) % n
    L[3] = (59-2*L[2]-L[5]) % n
    L[7] = (156-2*L[2]) % n

    for b in factor_base:
        print(f"log_2({b}) = {L[b]}")
        check = pow(alpha, L[b], p)
        print(f"check: 2^{L[b]} mod {p} = {check}")

    print("")
    print("Part C")
    print("")

if __name__ == "__main__":
    main()