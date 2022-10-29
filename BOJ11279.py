import heapq
from sys import stdin
heap = []
number = int(stdin.readline())

for i in range(number):
    N = int(stdin.readline())

    if N == 0:
        if heap:
            print(heapq.heappop(heap)[1])
        else:
            print("0")
        
    else:
        heapq.heappush(heap, [-N, N])