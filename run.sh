#!/bin/bash
set -x

flag=0
for i in {1..20}; do
    program_output=$( "./Series3/highway.exe" < "highway/input$i.txt" )
    expected_output=$(< "highway/output$i.txt" )  # Use redirection for expected_output
    if [ "$program_output" != "$expected_output" ]; then
        flag=1
        echo "Input $i:"
        echo "Expected $expected_output"
        echo "But got $program_output"
        echo -------
    fi
done

if [ $flag -eq 0 ]; then
    echo "Everything is good"
fi
