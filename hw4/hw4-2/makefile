C=gcc
TARGET=Encrypt
SRC=hw4-2.c operation.c AES.c DES.c SM4.c

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(C) $+ -o $@

-include $(SRC:.c=.d)

clean:
	$(RM) *.o *.d $(TARGET)

.PHONY: all clean
