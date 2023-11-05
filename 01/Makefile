CC = g++
CC_FLAGS = -std=c++20 
CC_GTEST_FLAGS=-lgtest_main -lgtest -lpthread

all: main test_bin

test_bin: PhoneticAlg.o test.cpp
	$(CC) $(CC_FLAGS) PhoneticAlg.o test.cpp -o test_bin $(CC_GTEST_FLAGS)

main: main.o PhoneticAlg.o
	$(CC) $(CC_FLAGS) -o main main.o PhoneticAlg.o

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp

PhoneticAlg.o: PhoneticAlg.cpp
	$(CC) $(CC_FLAGS) -c PhoneticAlg.cpp

test:
	./test_bin

clean: 
	rm -f *.o main