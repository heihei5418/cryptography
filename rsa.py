#-*-coding:utf-8-*-

class RSA(object):

    def __init__(self, p, q):
        self.p, self.q = p, q
        self.n = p * q
        self.phi_n = (p - 1) * (q - 1)
        '''k1 is the public key'''
        self.k1 = 65537
        self.gen_key(p, q)


    '''extended Euclidean algorithm'''
    def modular_integers(self, a, n):
        t0, t1 = 0, 1
        r0, r1 = n, a
        while r1 != 0:
            q = r0 // r1
            t0, t1 = t1, t0 - q * t1
            r0, r1 = r1, r0 - q * r1
        assert(r0 <= 1)
        if t0 < 0:
            t0 += n
        return t0


    def exp_mod(self, m, e, n):
        result = 1
        while e > 0:
            if e & 1 == 1:
                result = result * m % n
            e >>= 1
            m = m * m % n
        return result

    '''k2 is the private key'''
    def gen_key(self, p, q):
        self.k2 = self.modular_integers(self.k1, self.phi_n)


    def encrypt(self, m):
        temp = 0
        for item in m:
            temp *= 100000
            temp += ord(item)
        return self.exp_mod(temp, self.k1, self.n)


    def decrypt(self, c):
        c = int(c)
        temp = self.exp_mod(c, self.k2, self.n)
        s = ''
        while temp != 0:
            s += chr(temp % 100000)
            temp //= 100000
        s = s[::-1]
        return s


if __name__ == '__main__':
    '''RSA-768 numbers'''
    p = 33478071698956898786044169848212690817704794983713768568912431388982883793878002287614711652531743087737814467999489
    q = 36746043666799590428244633799627952632279158164343087642676032283815739666511279233373417143396810270092798736308917
    rsa = RSA(p, q)
    context = "我不懂，aaaaa"
    c = rsa.encrypt(context)
    print('密文：', c)
    m = rsa.decrypt(c)
    print('明文：', m)
