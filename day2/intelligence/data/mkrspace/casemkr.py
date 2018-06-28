from random import *
from os import *

RI = raw_input()

try:
	F, N, M, S = RI.split()
except:
	F, N, M = RI.split()
	S = "N"

N = int(N)
M = int(M)
NN = []
MM = []

LN = 10**6
LM = 2*10**6

if not 'S' in set(list(S)):
	for i in xrange(10):
		NN.append(N)
		MM.append(M)
		LN -= N
		LM -= M
else:
	for i in xrange(min(50, LN / N, LM / M)):
		NN.append(N)
		MM.append(M)
		LN -= N
		LM -= M

def random_split(N, M, Min):
	N -= M * Min
	assert N >= 0
	C = [Min] * M
	for i in xrange(N):
		C[randint(0, M - 1)] += 1
	return C

if not 'S' in set(list(S)):
	if N <= 2000 or M <= 4000:
		while LN >= 0 and LM >= 0:
			NNN = randint(1, N)
			MMM = randint(0, M)
			LN -= NNN
			LM -= MMM
			NN.append(NNN)
			MM.append(MMM)
	else:
		NA = randint(20, LN - 2000)
		MA = randint(40, LM - 4000)
		A = NA / 20
		B = (LN - NA) / 2000
		NN += random_split(NA, A, 1) + random_split(LN - NA, B, 1)
		MM += random_split(MA, A, 0) + random_split(LM - MA, B, 0)

assert len(NN) == len(MM)

system("g++ mkr.cpp -o mkr -O2")

system("echo %d > %s" % (len(NN), F))

OP = [[NN[i], MM[i]] for i in xrange(len(NN))]
shuffle(OP)
MAXN = N
MAXM = M
for (N, M) in OP:
	SS = S
	assert N <= MAXN and M <= MAXM
	if N != MAXN or M != MAXM:
		if randint(1, 10) == 1:	SS += 'A'
		if randint(1, 10) == 1:	SS += 'B'
		if randint(1, 10) == 1 and not 'D' in SS:	SS += 'C'
		if randint(1, 10) == 1 and not 'C' in SS:	SS += 'D'
	if 'C' in SS:
		M = min(N, M)
	system("echo %d %d %s %d | ./mkr >> %s" % (N, M, SS, randint(1, 10**9), F))
