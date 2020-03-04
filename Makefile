FLAGS = -Wall -Wextra -DDebug -g -std=c++14

all: predictors

Branch.o: Branch.cpp
	g++ $(FLAGS) -c Branch.cpp -o Branch.o

predictors: predictors.o Branch.o
	g++ $(FLAGS) predictors.o Branch.o -o predictors

predictors.o: predictors.cpp 
	g++ $(FLAGS) -c predictors.cpp -o predictors.o

clean:
	rm -rf predictors
	rm -rf *.o

run: all
	./predictors test_input.txt 
