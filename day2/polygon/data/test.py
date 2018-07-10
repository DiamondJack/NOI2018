import os
import sys

prog1=sys.argv[1]
prog2=sys.argv[2]

for x in sorted(os.listdir()):
	if len(x)>3:
		if x[-3:]=='.in':
			print(x)
			os.system('./%s <%s >tmp1.txt'%(prog1,x))
			os.system('./%s <%s >tmp2.txt'%(prog2,x))
			os.system('diff -w tmp1.txt tmp2.txt')



