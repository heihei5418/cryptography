CC = gcc
objects = hw4-2.o operation.o AES.o DES.o SM4.o mode.o

Hash : $(objects)
	gcc -o Encrypt $(objects)

$(objects) : operation.h

.PHONY : clean
clean :
	del Encrypt $(objects)
