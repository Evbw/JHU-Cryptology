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
    print()

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

if __name__ == "__main__":
    main()