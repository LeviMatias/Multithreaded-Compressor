# TP2-Multithreaded-Compressor

`/tp <B> <T> <Q> <infile> <outfile>`

Task: create a compressor console app that reads from a file with 4-byte numbers

The program will have <T> reading threads that will read a block of size B from the 
infile in a round robin fashion, it must then process and deposit the results in a 
queue that can store up to <Q> elements.
Simultaneously there must be another thread reading from such queues, also in round
robin, and storing the results in the outfile.

Objectives:
Implement the whole program using RAII
Practive the use of standard library structures, specially:
std::threads
std::mutex
std::conditional_variable

Thread Structure and Flow Chart
![alt text](https://github.com/LeviMatias/TP2-Multithreaded-Compressor/blob/master/diagram.png)
