#!/bin/bash

flag=0
for i in {1..22}
    do
        program_output=$( "./ch" < "chocolate/input$i.txt" )
        expected_output=$( cat "chocolate/output$i.txt" )
        if [ $program_output != $expected_output ]
        then
            flag = 1
            echo "Input $i:"
            echo "Expected $expected_output"
            echo "But got $program_output"
            echo -------
        fi
    done
if [ $flag != 1 ]; then echo Everything good; fi