main.exe : main.o BigNum.cpp
	g++ main.o BigNum.cpp -o main.exe

main.o : main.cpp
	g++ main.cpp -c main.o

BigNum.o : BigNum.cpp
	g++ BigNum.cpp -c BigNum.o
	