CC = g++
CC_FLAGS = -std=c++20
CC_GTEST_FLAGS = -lgtest_main -lgtest -lpthread #-l/opt/homebrew/Cellar/googletest/1.14.0/include/gtest/gtest.h

# all: main test_bin

# test_bin: stemmer.o test.cpp
# 	$(CC) $(CC_FLAGS) stemmer.o test.cpp -o test_bin $(CC_GTEST_FLAGS)

# main: stemmer.o main.o
# 	$(CC) $(CC_FLAGS) -o main main.o stemmer.o

# main.o: main.cpp
# 	$(CC) $(CC_FLAGS) -c main.cpp

# stemmer.o: stemmer.cpp
# 	$(CC) $(CC_FLAGS) -c stemmer.cpp

# test:
# 	./test_bin

# clean: 
# 	rm -f *.o main

CC = g++
CC_FLAGS = -std=c++20
CC_GTEST_FLAGS = -lgtest_main -lgtest -lpthread

all: stemmer_lib main test_bin

stemmer_lib: stemmer.o
	ar rcs libstemmer.a stemmer.o

test_bin: stemmer_lib test.cpp
	$(CC) $(CC_FLAGS) test.cpp -o test_bin -L. -lstemmer $(CC_GTEST_FLAGS)

main: stemmer_lib main.o
	$(CC) $(CC_FLAGS) -o main main.o -L. -lstemmer

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp

stemmer.o: stemmer.cpp
	$(CC) $(CC_FLAGS) -c stemmer.cpp

test:
	./test_bin

clean: 
	rm -f *.o main test_bin libstemmer.a