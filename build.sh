#!/bin/bash

g++ -std=c++20 -Werror -Wuninitialized -o server/release src/*.cpp -lprimesieve -lpqxx -lefsw
cd server
npm update