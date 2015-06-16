simulator.out: main.o city.o plane.o airport.o
	g++ -Wall -ansi -lm -g -o simulator.out city.o main.o plane.o airport.o

city.o: city.cpp city.h 
	g++ -Wall -ansi -g -c city.cpp

main.o: main.cpp plane.h airport.h list.h list.cpp
	g++ -Wall -ansi -g -c main.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -g -c plane.cpp

airport.o: airport.cpp airport.h city.h list.h list.cpp
	g++ -Wall -ansi -g -c airport.cpp

clean:
	rm -f simulator.out city.o main.o plane.o airport.o core
