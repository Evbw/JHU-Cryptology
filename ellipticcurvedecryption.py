import math

def modinv(val, p):
    return pow(val, p - 2, p)

def point_add(P, Q, p):
    x1 = P[0]
    y1 = P[1]
    x2 = Q[0]
    y2 = Q[1]
    lam = ((y2 - y1) * modinv(x2 - x1, p)) % p
    x3 = (lam * lam - x1 - x2) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def point_negate(P, p):
    return (P[0], (-P[1]) % p)

def point_double(P, a, p):
    x1 = P[0]
    y1 = P[1]
    lam = ((3 * x1 * x1 + a) * modinv(2 * y1, p)) % p
    x3 = (lam * lam - 2 * x1) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def f(x, a, b, p):
    return (x*x*x + a*x + b) % p

def double_and_add(k, P, a, p):
    result = None
    current = P
    while k > 0:
        if k % 2 == 1:
            if result is None:
                result = current
            elif result == current:
                result = point_double(current, a, p)
            else:
                result = point_add(result, current, p)
        current = point_double(current, a, p)
        k //= 2
    return result

def point_decompress(x, i, a, b, p):
    z = (x * x * x + a * x + b) % p
    if pow(z, (p - 1) // 2, p) !=1 and z != 0:
        return None 
    y = pow(r, (p + 1) // 4, p)
    if y % 2 == i:
        return (x, y)
    else:
        return (x, p - y)

def decrypt(C1, C2, m, a, b, p):
    C1 = point_decompress(C1[0], C1[1], a, b, p)

def main():
    a = 193
    b = 647
    p = 4339
    P = (719, 3538)
    Q = (3509, 334)

    #Part A: Find private key m
    for m in range(1, 4339):
        if double_and_add(m, P, a, p) == Q:
            print(f"m = {m}")
            break
    
    #Part B: Decrypt ciphertext
    ciphertext = [((3103, 1), 1860), ((745, 1), 1308), ((2214, 0), 981),
                  ((3210, 0), 3601), ((1222, 0), 3579), ((3643, 0), 2402),
                  ((1449, 0), 1871), ((3450, 1), 584), ((556, 1), 3019),
                  ((3945, 0), 148), ((468, 0), 4242), ((277, 0), 2557),
                  ((1460, 0), 3434), ((711, 0), 1522), ((3034, 1), 3293),
                  ((1565, 0), 848)] 

    plaintext = []
    for C1, C2 in ciphertext:
        pt = decrypt(C1, C2, m, a, b, p)

if __name__ == "__main__":
    main()