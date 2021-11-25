CC = g++
LIBS =
CFLAGS = -Wall -std=c++11
OBJECTS = bubblesort.o
OBJECTS2 = merge.o
TARGET = bubblesort.out
TARGET2 = merge.out
all: merge.out bubblesort.out

%.o : %.cpp $(HFILES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

$(TARGET2) : $(OBJECTS2)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS2) -o $(TARGET2)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o *.out core
