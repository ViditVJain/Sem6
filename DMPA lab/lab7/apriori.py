import csv,itertools

def cmp(t1, t2):
  return sorted(t1) == sorted(t2)

def findsubsets(S,m):
    return set(itertools.combinations(S, m))

transactions=[]
items=[]

with open('sample123.csv') as csvfile:
    readCSV = csv.reader(csvfile, delimiter=',')
    for row in readCSV:
        transactions.append(row)
        for ele in row:
            if ele not in items and ele !='':
                items.append(ele)

minSupport = int(input("Enter minimum support : "))

L1={}
for i in items:
    c=0
    for ele in transactions:
        c=c+ele.count(i)
    if(c>=minSupport):
        L1[i]=c

print("L1: ",L1)

C2={}
L2={}
L1items=list(L1.keys())
L1items.sort()
combos=list(itertools.combinations(L1items, 2))
for i in combos:
    C2[i]=0
for ele in C2:
    c=0
    for x in transactions:
        m=0
        for i in ele:
            if i in x:
                m=m+1
        if m==len(ele):
            c=c+1
    C2[ele]=c
    if(c>=minSupport):
        L2[ele]=c

print("L2: ",L2)
L2items=list(L2.keys())
L2items.sort()

L3t=[]
#generate combos of L2 with first item common
for i in L2items:
    for j in L2items:
        if(cmp(i,j)==False):
            #not equal
            if(i[0]==j[0]):
                checking=sorted(tuple(set(i+j)))
                if (checking not in L3t):
                    L3t.append(checking)

L3={}
C3=[]
y={}
for i in L3t:
    #generate subsets of i and check if it is frequent
    c=0
    sub=findsubsets(i,2)
    for j in sub:
        if(j in L2items):
            c=c+1
    if(c==len(sub)):
        C3.append(tuple(i))
for i in C3:
  y[i]=0
  for ele in y:
    c=0
    for x in transactions:
        m=0
        for i in ele:
            if i in x:
                m=m+1
        if m==len(ele):
            c=c+1
    y[ele]=c
    if(c>=minSupport):
        L3[ele]=c

print("L3: ",L3)
