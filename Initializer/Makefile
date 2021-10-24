CC = gcc
CFLAGS = 
LDFLAGS = -lpthread
OBJFILES = main.o ../Process_Generator/ProcessArray/ProcessArray.o ../Process_Generator/Process/Process.o ../Process_Generator/MemoryArray/MemoryArray.o
TARGET = ./build/out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) *~