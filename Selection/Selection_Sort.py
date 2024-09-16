Unsorted = [1, 7, 55, 32, 5, 2];

for i in range(len(Unsorted)-1):
    minInd = i;
    for j in range(i+1, len(Unsorted)):
        if Unsorted[minInd] > Unsorted[j]:
            minInd = j;
    Unsorted[i], Unsorted[minInd] = Unsorted[minInd], Unsorted[i];
    
    
for i in range(len(Unsorted)):
    print(Unsorted[i],end=" ");
