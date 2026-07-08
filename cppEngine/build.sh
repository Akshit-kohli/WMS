#!/bin/zsh

echo "Building Weighbridge Management System..."

g++ main.cpp serial.cpp weight.cpp transaction.cpp receipt.cpp api.cpp \
    -o weighbridge \
    -pthread \
    -std=c++17 \
    -Wall

if [ $? -eq 0 ]; then
    echo "Build successful! Run ./weighbridge to start."
else
    echo "Build failed. Check errors above."
fi