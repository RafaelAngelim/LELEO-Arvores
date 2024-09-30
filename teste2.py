import random
import matplotlib.pyplot as plt
import time

def Selection(arr):
    for i in range(len(arr)):
        minIND = i
        for j in range(i + 1, len(arr)): 
            if arr[j] < arr[minIND]:
                minIND = j
        arr[i], arr[minIND] = arr[minIND], arr[i]

def Insertion(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j+1] = arr[j]
            j -= 1
        arr[j + 1] = key

def Merge(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]
        Merge(L)
        Merge(R)
        
        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def Heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    
    if left < n and arr[left] > arr[largest]:
        largest = left
    if right < n and arr[right] > arr[largest]:
        largest = right
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        Heapify(arr, n, largest)

def Heap(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        Heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        Heapify(arr, i, 0)

def Partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def Quick(arr):
    def recur(arr, low, high):
        if low < high:
            pi = Partition(arr, low, high)
            recur(arr, low, pi - 1)
            recur(arr, pi + 1, high)
    recur(arr, 0, len(arr) - 1)

def ranArr(size):
    return [random.randint(1, 10000000000) for _ in range(size)]

def execTime(modulo, arr):
    st = time.time()
    modulo(arr)
    elapsed_time = time.time() - st
    return max(elapsed_time, 1e-9) 

def avgExecTime(modulo, arr, rep=3):
    tot = 0
    for _ in range(rep):
        arrI = arr.copy()
        tot += execTime(modulo, arrI)
    return tot / rep

def plotar(ASs, Time):
    for modulo, temp in Time.items():
        plt.plot(ASs, temp, label=modulo)
        
    plt.xlabel('Arr Size (log scale)')
    plt.ylabel('Tempo de exec (s)')
    plt.title('Comparacao')
    plt.legend()
    plt.xscale('log')
    
    all_positive = all(temp > 0 for tempos in Time.values() for temp in tempos)
    if all_positive:
        plt.yscale('log')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    ASs = [10 ** i for i in range(1, 7)]
    
    tempExec = {
        'Insertion': [],
        'Selection': [],
        'Merge': [], 
        'Heap': [], 
        'Quick': []
    }

    for size in ASs:
        arr = ranArr(size)
        print(f"\nTamanho do array: {size}")
        tempExec['Insertion'].append(avgExecTime(Insertion, arr))
        print(f"Insertion Sort: {tempExec['Insertion'][-1]:.6f} segundos")
        
        tempExec['Selection'].append(avgExecTime(Selection, arr))
        print(f"Selection Sort: {tempExec['Selection'][-1]:.6f} segundos")
        
        tempExec['Merge'].append(avgExecTime(Merge, arr))
        print(f"Merge Sort: {tempExec['Merge'][-1]:.6f} segundos")
        
        tempExec['Heap'].append(avgExecTime(Heap, arr))
        print(f"Heap Sort: {tempExec['Heap'][-1]:.6f} segundos")
        
        tempExec['Quick'].append(avgExecTime(Quick, arr))
        print(f"Quick Sort: {tempExec['Quick'][-1]:.6f} segundos")

    plotar(ASs, tempExec)
