import math

def f(x, a, b, p):
    return (x*x*x + a*x + b) % p        #Evaluate the right-hand side of the elliptic curve equation

def main():
    a = 1                               #Given paramaters for y^2 = x^3 + x + 28 over Z_71
    b = 28
    p = 71

    testexp = (p-1)//2                  #Euler's criterion exponent
    rootexp = (p+1)//4                  #Square root exponent

    for x in range(0,p):                #Enumerate all points on the curve via the x-coordinate
        r = f(x, a, b, p)
        if pow(r,testexp,p) == 1:       #If r is quadratic residue, there are two square roots +y and -y
            y1 = pow(r,rootexp,p)
            y2 = (-y1) % p
            print(f"({x}, {y1})")
            print(f"({x}, {y2})")
        if r == 0:                      #If r = 0, then y = 0
            print(f"({x}, 0)")

if __name__ == "__main__":
    main()