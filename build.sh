#!/bin/bash

g++ -std=c++14 -g -Werror -Wuninitialized -o build/test src/*.cpp -lprimesieve
