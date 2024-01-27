#!/bin/bash

flag=0
start_time=$(date +%s) # Record start time

for i in {1..22}; do 
    start_time=$(date +%s) 
    program_output=$( "Series2/relay.exe" < "relay/input$i.txt" )
    
    end_time=$(date +%s) # Record end time
    expected_output=$(< "relay/output$i.txt" ) # No need for cat here, using redirection
    execution_time=$((end_time - start_time)) # Calculate execution time in seconds


    echo "Execution time of input $i: $execution_time seconds"

    if [ "$program_output" != "$expected_output" ]; then
        flag=1
        echo "Input $i:"
        echo "Expected $expected_output"
        echo "But got $program_output"
        echo ---------
    fi
done


if [ $flag != 1 ]; then 
    echo "Everything good"
fi