#!/usr/bin/env bash
cd src
g++ *.cpp -o main.out
cd ../
# I'll execute my programs, with the input directory paymo_input and output the files in the directory paymo_output
./src/main.out ./paymo_input/batch_payment.txt ./paymo_input/stream_payment.txt ./paymo_output/output1.txt ./paymo_output/output2.txt ./paymo_output/output3.txt

