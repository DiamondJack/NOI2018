while
python3 gen.py >1.in
time ./std <1.in >std.out
time ./hhd <1.in >hhd.out
diff -w std.out hhd.out
do :; done