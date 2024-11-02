# Makefile

CC = gcc
SRCS = main.c student_records.c tinyfiledialogs.c
TARGET = student_program

.PHONY: all clean run

all: $(TARGET)

$(TARGET):
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
