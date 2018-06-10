n=(-1 5 60 60 60 60 60 60 200 200 200)
Q=(-1 21 199992 23 199994 199995 199996 199997 199998 199999 200000)
C=(-1 6 500 6 500 500 0 500 1000 1000 1000)
Type=(-1 0 1 2 2 0 0 4 0 0 0)

seedList=$(cat seed.txt)

i=0
make gen

for seed in $seedList
do
	((++i))
	echo "./gen $seed ${n[i]} ${Q[i]} ${C[i]} ${Type[i]} >$i.in"
	./gen $seed ${n[i]} ${Q[i]} ${C[i]} ${Type[i]} >$i.in
done
