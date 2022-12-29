N = int(input())
arr = list(map(int, input().split()))

for i in range(N):
    if arr[i] == (int(arr[i] ** 0.5) ** 2):
        print(1, end = " ")
    else:
        print(0, end = " ")