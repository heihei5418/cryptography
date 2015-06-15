CC = gcc
objects = hw4-3.o operation.o AES.o GCM.o

Hash : $(objects)
	gcc -o Encrypt $(objects)

$(objects) : operation.h

.PHONY : clean
clean :
	del Encrypt $(objects)
