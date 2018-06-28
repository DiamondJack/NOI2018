DST=../../data/

./genIn.sh
./encrypt.sh 1 20
./getAns.sh 1 20
for ((i=1;i<=20;++i)); do
	mv $i.in ${DST}/
	mv $i.ans ${DST}/
done