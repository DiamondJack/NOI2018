cp ../wyz/std.cpp std.cpp
make std
for ((i=1;i<=10;++i))
do
	time ./std <$i.in >$i.ans
done
