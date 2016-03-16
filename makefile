NDIsing: main.o  Markov.o NDIsing.o Output.o
	clang++ -std=c++11 -o NDIsing main.o Markov.o NDIsing.o Output.o
main.o: main.cpp NDIsing.h
	clang++ -std=c++11 -o main.o -c main.cpp
NDIsing.o: NDIsing.h NDIsing.cpp
	clang++ -std=c++11 -o NDIsing.o -c NDIsing.cpp
Markov.o: Markov.cpp NDIsing.h
	clang++ -std=c++11 -o Markov.o -c Markov.cpp
Output.o: Output.cpp NDIsing.h
	clang++ -std=c++11 -o Output.o -c Output.cpp
clean:
	rm *.o