#!/bin/bash

read -p "Enter words file (e.g., words.txt): " wordsFileName
read -p "Enter grid file (e.g., 4x7.grid.txt): " gridFileName
read -p "Enter output file (e.g., output.txt): " outputFileName

if [[ -z "$wordsFileName" ]]; then
  wordsFileName="words.txt"
fi

if [[ -z "$gridFileName" ]]; then
  gridFileName="140x70.grid.txt"
fi

if [[ -z "$outputFileName" ]]; then
  outputFileName="output.txt"
fi

RUNNING_TIME1=`clang++ timer.cpp hash_table/hash.cpp grid.cpp main.cpp -std=c++11 -g -O2 ; ./a.out $wordsFileName $gridFileName $outputFileName | tail -1`
result1=$(echo "$RUNNING_TIME1 * 1000" | bc -l)

RUNNING_TIME2=`./a.out $wordsFileName $gridFileName $outputFileName | tail -1`
result2=$(echo "$RUNNING_TIME1 * 1000" | bc -l)

RUNNING_TIME3=`./a.out $wordsFileName $gridFileName $outputFileName | tail -1`
result3=$(echo "$RUNNING_TIME1 * 1000" | bc -l)

RUNNING_TIME4=`./a.out $wordsFileName $gridFileName $outputFileName | tail -1`
result4=$(echo "$RUNNING_TIME1 * 1000" | bc -l)

RUNNING_TIME5=`./a.out $wordsFileName $gridFileName $outputFileName | tail -1`
result5=$(echo "$RUNNING_TIME1 * 1000" | bc -l)


sum=$(echo "$result1 + $result2 + $result3 + $result4 + $result5" | bc)
quotient=5.0
average=$(echo "$sum / $quotient" | bc)
echo "average time = $average milliseconds"

