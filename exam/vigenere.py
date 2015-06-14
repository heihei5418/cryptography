mode = input("加密0 or 解密1 ?")
context = []
key = ""
cipher = []
if int(mode) == 0:
    context = input("请输入明文: ")
    key = input("请输入密钥: ")
    ksize = len(key)
    for i in range(len(context)):
        cipher.append((ord(context[i])+ord(key[i%ksize]))%26)
    for i in range(len(cipher)):
        print(chr(cipher[i]+ord('A')), end='')
else:
    cipher = input("请输入密文: ")
    key = input("请输入密钥: ")
    ksize = len(key)
    for i in range(len(cipher)):
        context.append((ord(cipher[i])-ord(key[i%ksize]))%26)
    for i in range(len(context)):
        print(chr(context[i]+ord('A')), end='')
