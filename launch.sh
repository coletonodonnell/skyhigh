#!/bin/bash

server/release &
nodemon server/index.js &

trap ctrl_c INT

function ctrl_c() {
    trap "trap - SIGTERM && kill -- -$$" SIGINT SIGTERM EXIT
}

while true; do
    sleep 1
    echo -n "."
done