C=gcc
TARGET=Hash
SRC=hw4-1.c operation.c SHA1.c SHA2.c SHA3.c

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(C) $+ -o $@

-include $(SRC:.c=.d)

clean:
	$(RM) *.o *.d $(TARGET)

.PHONY: all clean
