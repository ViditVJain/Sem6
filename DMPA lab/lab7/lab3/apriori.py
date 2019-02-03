import csv
import itertools

itemset = []
dat =[]
rows = []
with open("thing.csv") as csvfile:
    creader = csv.reader(csvfile)
    itemset = next(creader)
    for row in creader:
        rows.append(row)

for i in range(len(rows)):
    tempset = []
    for j in range(len(rows[0])):
        if rows[i][j] == '1':
            tempset.append(itemset[j])
    dat.append(tuple(tempset))

min_sup = input("enter min support:")

# for sub in itertools.combinations(itemset, 2):
#     print(sub)

itemset = tuple(itemset)
for item in itemset:
    ct = 0
    for trans in dat:
        if item.issubset(trans):
            print(item, trans)

for i in range(len(rows[0])-1, -1, -1):
    ct = 0
    for j in range(len(rows)):
        if rows[j][i] == '1':
            ct += 1
        print(rows[j][i], end="")
    print(" ", ct, end="")
    if ct < int(min_sup):
        del itemset[i]
    print()

print(itemset)
print(dat)


