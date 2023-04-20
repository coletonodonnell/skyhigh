#!/bin/bash

g++ -std=c++17 -g -Werror -Wuninitialized -o build/test src/*.cpp -lprimesieve -lpqxx