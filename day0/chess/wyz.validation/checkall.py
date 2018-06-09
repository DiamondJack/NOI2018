import json
import os

with open('../tables/table.json','r') as f:
	tbl=json.load(f);

os.system("make validate")
for i in range(1,len(tbl)):
	a=[ x.replace('$','') for x in tbl[i] ]
	index=list(map(int,a[0].split(',')))
	for j in index:
		os.system("./validate ../data/%d.in %d %s %s" %(j,j,a[1],a[2]))
for j in range(1,3):
	os.system("./validate ../down/%d.in" %(j))
