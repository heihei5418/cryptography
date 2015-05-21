CC = gcc
objects = hw4-1.o operation.o SHA1.o SHA2_256.o SHA2_512.o SHA3_256.o SHA3_512.o SM3.o

Hash : $(objects)
	gcc -o Hash $(objects)

$(objects) : operation.h

.PHONY : clean
clean :
	del Hash $(objects)