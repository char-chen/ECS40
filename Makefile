simulator.out: city.o main.o citylist.o plane.o
	g++ -Wall -ansi -lm -g -o simulator.out city.o main.o plane.o citylist.o

city.o: city.cpp city.h 
	g++ -Wall -ansi -g -c city.cpp

main.o: main.cpp citylist.h plane.h 
	g++ -Wall -ansi -g -c main.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -g -c plane.cpp

citylist.o: citylist.cpp citylist.h city.h
	g++ -Wall -ansi -g -c citylist.cpp

clean:
	rm -f simulator.out city.o main.o citylist.o plane.o core
