CC = gcc
CFLAGS = 
LDFLAGS = -lpthread
OBJFILES = main.o ProcessArray/ProcessArray.o Process/Process.o MemoryArray/MemoryArray.o Generator/Generator.o ../Spy/Logger/logger.o Menu/menu.o
TARGET = ./build/out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) *~