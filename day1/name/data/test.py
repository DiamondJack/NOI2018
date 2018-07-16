import os
import sys

prog=sys.argv[1]

for x in sorted(os.listdir()):
	if len(x)>3:
		if x[-3:]=='.in':
			print(x)
			os.system('./%s <%s >tmp.txt'%(prog,x))
			os.system('diff -w %s.ans tmp.txt'%(x[:-3]))












