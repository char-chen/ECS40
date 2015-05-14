simulator.out: city.o main.o plane.o
	g++ -Wall -ansi -lm -g -o simulator.out city.o main.o plane.o

city.o: city.cpp city.h 
	g++ -Wall -ansi -g -c city.cpp

main.o: main.cpp list.h list.cpp plane.h 
	g++ -Wall -ansi -g -c main.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -g -c plane.cpp

clean:
	rm -f simulator.out city.o main.o plane.o core
