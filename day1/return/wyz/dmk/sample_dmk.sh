DST=../../down/
SEED=19260817
./gen ${SEED} 1 1000 2500 2000 0 1 0 >3.in
./gen ${SEED} 1 2000 5000 4000 2 0 1 >4.in
./gen ${SEED} 1 100000 200000 150000 0 0 0 >5.in
./encrypt.sh 3 5
./getAns.sh 3 5
for ((i=3;i<=5;++i)); do
	mv $i.in ${DST}/
	mv $i.ans ${DST}/
done