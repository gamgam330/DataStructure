N = int(input())
arr = list(map(int, input().split()))
cnt = 0
find = int(input())

for i in range(N):
    if(arr[i] == find):
        cnt += 1

print(cnt)
