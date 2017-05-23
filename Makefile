HugeInt:HugeInt.o
	g++ -o HugeInt HugeInt.o

HugeInt.o:HugeInt.cpp
	g++ -c HugeInt.cpp

clean:
	rm HugeInt *.o
