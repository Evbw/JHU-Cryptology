import math

def isNonSingular(a, b, p):
    return 0 != (( 4*a*a*a + 27*b*b) % p)

def f(x, a, b, p):
    return (x*x*x + a*x + b) % p

def main():
    a = 1
    b = 28
    p = 71
    quadres = set()

    if not isNonSingular(a, b, p):
        print("Invalid value")
        return 0
    
    for x in range(1,p):
        qr = (x*x) % p
        quadres.add(qr)

    for quad in quadres:
        print(quad)

    print( (p%4) == 3)
    testexp = (p-1)//2
    rootexp = (p+1)//4
    print("Test exponent: ", testexp)
    print("Root exponent: ", rootexp)

    for x in range(0,p):
        r = f(x, a, b, p)
        if pow(r,testexp,p) == 1:
            y1 = pow(r,rootexp,p)
            y2 = (-y1) % p
            print('(',x,',', y1,')')
            print('(',x,',',y2,')')
        if r == 0:
            print('(',x,',','0)')

if __name__ == "__main__":
    main()