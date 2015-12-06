#!/bin/bash

ARGS=''

if [[ $user ==  'jenkins' ]] 
then
	ARGS='--log_format=XML --log_sink=results.xml --log_level=all --report_level=no --result_code=no'
fi 

for i in ./test-*
do
      $i $ARGS
done
