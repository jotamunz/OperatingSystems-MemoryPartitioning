CC = gcc
CFLAGS = 
LDFLAGS = -lpthread
OBJFILES = main.o ProcessList/ProcessList.o Process/Process.o Memory/Memory.o
TARGET = ./build/out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) *~