cp ../wyz/std.cpp std.cpp
make std
for ((i=3;i<=4;++i))
do
	time ./std <$i.in >$i.ans
done

