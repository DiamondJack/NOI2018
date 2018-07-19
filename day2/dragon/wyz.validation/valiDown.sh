make validate
buffer=''
for ((i=1;;++i))
do
	if [ ! -e "../down/$i.in" ]
	then
		echo Sample#$i Nout Found.All the datas are checked!
		break
	fi
	./validate ../down/$i.in 0
	if (($?))
	then
		echo Boooooooooooooom!!!!
		read -n1 -s -p "Press Any Key To Continue..."
		buffer+=${i}', '
	fi
done
echo [ Invalid Testcase Id ]: ${buffer}
