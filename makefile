CC =gcc
CFLAGS = -Wall -g
TARGET = shell
all: $(TARGET)
$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)


clean:
	rm $(TARGET)
