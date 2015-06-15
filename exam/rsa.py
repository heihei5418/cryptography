p = int(input("p:"))
q = int(input("q:"))
mode = int(input("encode0 or decode1?"))
n = p * q
ans = 1
if mode == 0:
    a = int(input("public key:"))
    m = int(input("context:"))
    for i in range(a):
        ans *= m
        ans %= n
    print("cipher:", ans)
else:
    b = int(input("private key:"))
    c = int(input("cipher:"))
    for i in range(b):
        ans *= c
        ans %= n
    print("context:", ans)
