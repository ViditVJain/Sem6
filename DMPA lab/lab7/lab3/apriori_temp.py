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

# dat = set(dat)


min_sup = int(input("enter min support:"))

temset = set([])
for item in itemset:
    temset.add(item)
itemset = temset


###########################################################################################
# L = set([])
# for item in itemset:
#     ct = 0
#     for trans in dat:
#         if frozenset(item).issubset(trans):
#             print(item, trans)
#             ct+=1
#     if (ct>=min_sup):
#         L.add(item)
# itemset = copy.deepcopy(L)
# print("itemset(L): ", itemset)


# C = set([])
# for sub in itertools.combinations(itemset, 2):
#     print("subset : ", sub)
#     C.add(sub)
# print("\n\nC:\n", C)
# itemset = copy.deepcopy(C)

# L = set([])
# for item in itemset:
#     ct = 0
#     for trans in dat:
#         if frozenset(item).issubset(trans):
#             print(item, trans)
#             ct+=1
#     if (ct>=min_sup):
#         L.add(item)
# itemset = copy.deepcopy(L)
# print("itemset(L1): ", itemset)


# C = set([])
# for sub in itertools.combinations(itemset, 3):
#     print("subset : ", sub)
#     C.add(frozenset(sub))
# print("\n\nC1:\n", C)

##########################################################################################
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













# itemset = list(itemset)
##############################################
# for i in range(len(rows[0])-1, -1, -1):
#     ct = 0
#     for j in range(len(rows)):
#         if rows[j][i] == '1':
#             ct += 1
#         print(rows[j][i], end="")
#     print(" ", ct, end="")
#     if ct < int(min_sup):
#         del itemset[i]
#     print()
###############################################
# print("\n--------------------------\n\n\nitemset\n",itemset)
# print(dat)


# dat = tuple(dat)
# print("here : ", dat)
# itemset = tuple(itemset)
# print(itemset)
# for item in itemset:
#     ct = 0
#     print(item)
#     # if(item.issubset(dat)):
#         # print(item)
#     # for trans in dat:
#     #     if item.issubset(trans):
#     #         print(item, trans)
