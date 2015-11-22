# PNG_IFLAGS=`libpng-config --cflags`
# PNG_LDFLAGS=libpng-config --ldflags
CFLAGS=-g #-Wall #-std=c++11

all: clean test run_test

run_test:
	./test

test.o: test.cpp
	g++ $(CFLAGS) $< -c

%.o: %.cpp %.h
	g++ $(CFLAGS) $< -c

test: test.o
	g++ $(CFLAGS) $< -o $@

clean:
	rm -rf test *.o *~ */*~
