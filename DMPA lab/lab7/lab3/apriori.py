import csv
import itertools
import copy

itemset = []
dat = set([])
rows = []
with open("thing1.csv") as csvfile:
    creader = csv.reader(csvfile)
    itemset = next(creader)
    for row in creader:
        rows.append(row)

for i in range(len(rows)):
    tempset = set([])
    for j in range(len(rows[0])):
        if rows[i][j] == '1':
            tempset.add(itemset[j])
    dat.add(frozenset(tempset))

min_sup = int(input("enter min support:"))

temset = set([])
for item in itemset:
    temset.add(item)
itemset = temset


L = set([])
C = set([])
it = 2

while True:
    L = set([])
    for item in itemset:
        ct = 0
        for trans in dat:
            if frozenset(item).issubset(trans):
                ct+=1
        if (ct>=min_sup):
            L.add(item)
    itemset = copy.deepcopy(L)
    print("L", it-1, ": ", itemset)


    C = set([])
    for sub in itertools.combinations(itemset, it):
        C.add(sub)
    itemset = copy.deepcopy(C)
    print("\nC", it, " :", C)
    it+=1
    if (len(itemset)==0):
        break