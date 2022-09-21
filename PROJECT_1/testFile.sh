#! /bin/bash

get_random_line()
{
	n_lines=$(wc -l < $1)
	random_line=$((1 + RANDOM % $n_lines));
	line=$(cat $1|sed -n "${random_line}p")
}
monadiko_id()
{
	for i in ${arr[@]}
		do 
			if [ $id -eq $i ]
			then
				id=$((1 + RANDOM % 9999))
				monadiko_id arr id
			fi	
		done
}

get_eggrafi()
{
	id=$((1 + RANDOM % 9999))
	monadiko_id arr id
	arr+=($id)
	name=$(cat /dev/urandom | tr -dc 'a-zA-Z' | head -c $((3 + RANDOM % 10)) ) #echo "$name"
	surname=$(cat /dev/urandom | tr -dc 'a-zA-Z' | head -c $((3 + RANDOM % 10)) ) #echo "$surname"
	age=$((1 + RANDOM % 120))
	get_random_line $countr
	country=$line #echo "$country"
	get_random_line $vir
	virus=$line #echo "$virus"
	yn_array=("YES" "NO")
	thesi=$((RANDOM % 2))
	yn=${yn_array[$thesi]}
	if [ $yn = "YES" ]
	then
		dat=$(date -d "$((2019 + RANDOM % 3))-$((1 + RANDOM % 12))-$((1 + RANDOM % 30))" '+%d-%m-%Y')
	else
		dat=""
	fi
}

if [ $# -ne 4 ]
then
	echo "You gave wrong number of parameters,please try again"
elif [ $3 -le 1 ]
then
	echo "Please give at least 1 line"	
elif [ $4 -ne 0 -a $4 -ne 1 ]
then
	echo "dublicatedAllowed must take values 0 or 1 !"
else
	vir=$1
	echo "The viruses file is the $vir"
	countr=$2
	echo "The countries file is the $countr"
	nbl=$3
	echo "The number of lines is $nbl"
	dub=$4
	echo "The duplicate is $dub"

	if [ $dub -eq 0 ]
	then
		lines=1
		arr=()
		while [ $lines -le $nbl ]
		do
			get_eggrafi countr vir arr
			echo "$id $name $surname $country $age $virus $yn $dat" >> testinputfile.txt
			((lines++))
		done
	fi

	if [ $dub -eq 1 ]
	then
		lines=1
		arr=()
		while [ $lines -le $nbl ]
		do
			if [ $(($lines%10)) = 0 ]
			then
				number=$(($lines-2))
				id=${arr[$number]}
				arr+=($id)
				name=$(cat /dev/urandom | tr -dc 'a-zA-Z' | head -c $((3 + RANDOM % 10)) ) #echo "$name"
				surname=$(cat /dev/urandom | tr -dc 'a-zA-Z' | head -c $((3 + RANDOM % 10)) ) #echo "$surname"
				age=$((1 + RANDOM % 120))
				get_random_line $countr
				country=$line #echo "$country"
				get_random_line $vir
				virus=$line #echo "$virus"
				yn_array=("YES" "NO")
				thesi=$((RANDOM % 2))
				yn=${yn_array[$thesi]}
				if [ $yn = "YES" ]
				then
					dat=$(date -d "$((2019 + RANDOM % 3))-$((1 + RANDOM % 12))-$((1 + RANDOM % 30))" '+%d-%m-%Y')
				else
					dat=""
				fi
				echo "$id $name $surname $country $age $virus $yn $dat" >> testinputfile.txt
				((lines++))
				continue
			fi
			get_eggrafi countr vir arr
			echo "$id $name $surname $country $age $virus $yn $dat" >> testinputfile.txt
			((lines++))
		done
	fi
fi
