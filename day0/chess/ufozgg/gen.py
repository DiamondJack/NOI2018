from random import *
name = "chess"
n=[0, 2, 2, 2, 3, 3, 3, 5, 5, 8, 8,10,10,10,10,10,10,10,10,10,10,5]
m=[0, 2, 2, 2, 3, 3, 3, 5, 5, 8, 8, 1, 1, 2, 2, 3, 3,10,10,10,10,5]

def gen(in_f,nn,mm,num):
	data = open(in_f,'w')
	data.write("%d %d\n"%(nn,mm))
	for i in range(nn):
		for j in range(mm):
			data.write(str(randint(0,100000)))
			if j != mm - 1:
				data.write(" ")
		data.write("\n")
	for i in range(nn):
		for j in range(mm):
			if num % 2 == 1:
				data.write("0")
			else:
				data.write(str(randint(0,100000)))
			if j != mm - 1:
				data.write(" ")
		data.write("\n")
	data.close()

if __name__ == '__main__':
	for i in range(1,22):
		in_f = '../data/' + str(i) + '.in'
		gen(in_f,n[i],m[i],i)
