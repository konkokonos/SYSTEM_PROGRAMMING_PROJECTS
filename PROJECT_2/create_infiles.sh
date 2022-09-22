#! /bin/bash

if [ $# -ne 3 ]
then
	echo "You gave wrong number of parameters,please try again"
elif [ $3 -le 0 ]
then
	echo "Please give at least 1 File per Directory"	
else
	input_file=$1
	echo "The input file is the $input_file"
	input_dir=$2
	echo "The input dir is the $input_dir"
	numFilesPerDirectory=$3
	echo "The number of lines is $numFilesPerDirectory"
fi

if [ ! -d "input_dir" ]
then
	mkdir $input_dir
else
	echo "This Directory exists,please rerun the bash script with a different Directory"
	exit 0
fi

arr=()

while read line
	do
		country=$(echo $line | awk '{print $4}')
		if [[ "${arr[@]}" =~ "${country}" ]]
		then
			continue
		else
			arr+=($country)
		fi	
	done < "$input_file"

for i in ${arr[@]}
do
	mkdir $input_dir/$i
	for (( j=1; j<=$numFilesPerDirectory; j++ ))
	do
		touch $input_dir/$i/$i-$j.txt
	done
done

#echo ${#arr[@]} #size of an array
times=()
for (( i=0; i<${#arr[@]}; i++ ))
	do
		times[i]=0
	done

while read line
	do
		country=$(echo $line | awk '{print $4}')
		for (( i=0; i<${#arr[@]}; i++ ))
			do
				if [[ "${arr[i]}" =~ "${country}" ]]
				then
					(( times[i]++ ))
					if [ ${times[$i]} -gt $numFilesPerDirectory ]
					then
						times[i]=1
					fi
					echo "$line" >> $input_dir/$country/$country-${times[$i]}.txt
				fi
			done
	done < "$input_file"

exit 0