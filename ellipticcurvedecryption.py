import math

def modinv(val, p):
    return pow(val, p - 2, p)                           #Computer modular inverse using Fermat's Little Theorem

def point_add(P, Q, p):
    x1 = P[0]                                           #Add points P and Q on an elliptic curve over F_p
    y1 = P[1]                                           #Using secant line formula (Case 1: x1 != x2)
    x2 = Q[0]                                           #lambda = (y2 - y1)/(x2 - x1)
    y2 = Q[1]
    lam = ((y2 - y1) * modinv(x2 - x1, p)) % p
    x3 = (lam * lam - x1 - x2) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def point_negate(P, p):
    return (P[0], (-P[1]) % p)                          #Compute Additive Inverse (Case 2: x1 = x2 and y1 = -y2)

def point_double(P, a, p):
    x1 = P[0]                                           #Double point p on the curve (Case 3: x1 = x2 and y1 = y2)
    y1 = P[1]                                           #lambda = (3x1^2 + a)/(2y1)
    lam = ((3 * x1 * x1 + a) * modinv(2 * y1, p)) % p
    x3 = (lam * lam - 2 * x1) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return (x3, y3)

def f(x, a, b, p):
    return (x*x*x + a*x + b) % p                        #Evaluate the right-hand side of the elliptic curve equation

def double_and_add(k, P, a, p):
    #Compute kP using the double and add algorithm
    #Processes k from least to most significant bit
    result = None                                       #Represents point at infinity until first add
    current = P                                         #Tracks 2^i * P as i increases
    while k > 0:
        if k % 2 == 1:                                  #Current bit is 1, so add current power of 2 of P to result
            if result is None:
                result = current
            elif result == current:                     #Points are equal, so double instead of using addition
                result = point_double(current, a, p)
            else:
                result = point_add(result, current, p)
        current = point_double(current, a, p)           #Double the current point for the next bit position
        k //= 2
    return result

def point_decompress(x, i, a, b, p):                    #Recover a curve point from it's compressed form
    z = (x * x * x + a * x + b) % p
    if pow(z, (p - 1) // 2, p) !=1 and z != 0:          #Check that z is a quadratic residue
        return None 
    y = pow(z, (p + 1) // 4, p)                         #Compute z^((p+1)/4) mod p
    if y % 2 == i:                                      #Select root with parity to bit i
        return (x, y)
    else:
        return (x, p - y)

def decrypt(C1, C2, m, a, b, p):
    C1 = point_decompress(C1[0], C1[1], a, b, p)        #Decrypt an ElGamal ciphertext block
    S = double_and_add(m, C1, a, p)                     #S = m * point_decompress(C1)
    plaintext = (C2 * modinv(S[0], p)) % p              #Unmask plaintext using the x-coordinate of the shared secret key
    return plaintext

def main():
    a = 193                                             #Parameters for y^2 = x^3 + 193x + 647 over Z_4339
    b = 647
    p = 4339
    P = (719, 3538)                                     #Public key components
    Q = (3509, 334)

    #Part A: Find private key m
    for m in range(1, 4339):
        if double_and_add(m, P, a, p) == Q:
            print(f"m = {m}")
            break
    
    #Part B: Decrypt ciphertext
    ciphertext = [
        ((3103, 1), 1860), ((745, 1), 1308), ((2214, 0), 981),
        ((3210, 0), 3601), ((1222, 0), 3579), ((3643, 0), 2402),
        ((1449, 0), 1871), ((3450, 1), 584), ((556, 1), 3019),
        ((3945, 0), 148), ((468, 0), 4242), ((277, 0), 2557),
        ((1460, 0), 3434), ((711, 0), 1522), ((3034, 1), 3293),
        ((1565, 0), 848)
    ] 

    plaintext = []
    for C1, C2 in ciphertext:
        pt = decrypt(C1, C2, m, a, b, p)
        plaintext.append(pt)
    print(f"Plaintext numbers: {plaintext}")

    #Part C: convert numbers to letters
    message = ""
    for pt in plaintext:
        message += chr(ord('A') + pt - 1)
    print(f"Message: {message}")

if __name__ == "__main__":
    main()