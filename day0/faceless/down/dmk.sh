cp ../gen.cpp gen.cpp
make gen
./gen 19260817 5 21 6 0 >3.in
./gen 19260817 40 190000 400 1 >4.in
./getAns.sh
rm gen gen.cpp std std.cpp
