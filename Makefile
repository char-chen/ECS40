simulator.out: vector.o city.o main.o
	g++ -g -ansi -Wall -o simulator.out vector.o city.o main.o

vector.o: vector.cpp vector.h city.h
	g++ -g -ansi -Wall -c vector.cpp

city.o: city.cpp city.h
	g++ -g -ansi -Wall -c city.cpp

main.o: main.cpp vector.h
	g++ -g -ansi -Wall -c main.cpp

clean:
	rm -f simulator.out *.o
