def Insertion(Unsorted):
    for i in range(1, len(Unsorted)):
        val = Unsorted[i];
        j = i-1;
        while j >= 0 and val < Unsorted[j]:
            Unsorted[j+1] = Unsorted[j];
            j-=1;
        Unsorted[j+1] = val;
        
Unsorted = [1, 7, 55, 32, 5, 2];
Insertion(Unsorted);

for i in range(len(Unsorted)):
    print(Unsorted[i], end=" ")

    