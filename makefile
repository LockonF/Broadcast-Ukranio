run: make
    ./main
make:
    g++ main.cpp PaqueteDatagrama.cpp SocketDatagrama.cpp -o main -std=c++11 -lpthread