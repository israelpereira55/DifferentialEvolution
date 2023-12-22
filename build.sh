#!/bin/bash

# bazel run src/main:main -- --instance file --k 10

echo "Cleaning old files."
rm -rf bin

echo "Compiling..."
if [ "$1" = "debug" ]; then
    echo "Debug mode activated."
    bazel build -c dbg src/main:main 
else
    bazel build src/main:main
fi

mkdir -p bin
cp bazel-bin/src/main/main bin/main
cp -r instances bin
cp -r settings bin