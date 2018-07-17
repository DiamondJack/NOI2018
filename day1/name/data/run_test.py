import os, sys

runname = sys.argv[1]

l = int(sys.argv[2])
r = int(sys.argv[3])

#os.system("g++ {0}.cpp -o {0} -O2".format(runname))

for x in range(l - 1, r):
	print(x)
	os.system("time ./{0} <./{1}.in >{0}.out {2} {3} {4} {5} {6}".format(runname, x + 1, sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8]))
	

