if (($#==0)); then
	echo "Too Few Arguments!"
	exit
fi

NAME=$1
make ${NAME}
for ((i=1;i<=20;++i)); do
	echo checking data#${i}
	time ./${NAME} <../data/${i}.in >output.out
	if diff output.out ../data/${i}.ans >diff.log.txt; then
		echo Accepted.
	else
		echo Wrong Anser!!!!
		exit
	fi
done
rm diff.log.txt
rm output.out
