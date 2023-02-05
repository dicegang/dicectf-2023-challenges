#include <iostream>
#include <vector>
#include <getopt.h>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "crb.cpp"
using namespace std;

int numThreads = 1;

template <typename T>
T op0(T x, T y) {
    return x + y;
}

template <typename T>
T op1(T x, T y) {
    return x * y;
}

template <typename T>
T op2(T x, T y) {
    return x ^ y;
}

template <typename T>
void parallel_prefix_scan(vector<T> &data, T (*op0)(T, T), T(*op1)(T, T), T(*op2)(T, T)) {
    thread threads[numThreads];
    crb bar(numThreads);

    T (* ops[])(T, T) = {op0, op1, op2};
    random_shuffle(ops, ops + 3);

    atomic_uint32_t index = 1;
    for (int i = 0; i < numThreads; i++) {
        threads[i] = thread([&data, &ops, &index, &bar]() {
            uint32_t stride = 1;
            while (stride <= data.size() / 2) {
                while (index * stride * 2 - 1 < data.size()) {
                    size_t localidx = index.fetch_add(1) * stride * 2 - 1;
                    if (localidx < data.size()) {
                        auto opidx = (int) round(log2(stride)) % 3;
                        data[localidx] = ops[opidx](data[localidx], data[localidx - stride]);
                    }
                }
                bar.sync();
                stride *= 2;
                index = 1;
                bar.sync();
            }

            while (stride > 0) {
                while (index * stride * 2 - 1 < data.size()) {
                    size_t localidx = index.fetch_add(1) * stride * 2 - 1;
                    if (localidx + stride < data.size()) {
                        auto opidx = (int) round(log2(stride)) % 3;
                        data[localidx + stride] = ops[opidx](data[localidx], data[localidx + stride]);
                    }
                }
                bar.sync();
                stride /= 2;
                index = 1;
                bar.sync();
            }
        });
    }
    for (int i = 0; i < numThreads; i++)
        threads[i].join();
}

int main(int argc, char ** argv) {
    int flag;
    ifstream infile;
    ofstream outfile;
    while ((flag = getopt(argc, argv, "n:i:o:")) != -1) {
        switch (flag) {
            case 'n':
                numThreads = max(numThreads, stoi(optarg));
                break;
            case 'i':
                infile.open(optarg);
                if (!infile.is_open()) cerr << "Failed to open input file\n";
                break;
            case 'o':
                outfile.open(optarg);
                break;
            default:
                cerr << "Unknown flag " << flag << endl;
                break;
        }
    }

    int nLines;
    infile >> nLines;
    srand(numThreads ^ nLines);

    vector<int64_t> data(nLines);
    for (int l = 0; l < nLines; l++)
        infile >> data[l];

    auto start = chrono::high_resolution_clock::now();

    parallel_prefix_scan(data, op0, op1, op2);

    auto end = chrono::high_resolution_clock::now();

    printf("%.17f\n", chrono::duration_cast<chrono::duration<double>>(end - start).count());

    for (int l = 0; l < nLines; l++) {
        outfile << data[l] << endl;
    }

    return 0;
}
