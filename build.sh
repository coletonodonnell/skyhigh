#!/bin/bash

g++ -std=c++20 -g -Werror -Wuninitialized -o build/test src/*.cpp -lprimesieve -lpqxx -lefsw