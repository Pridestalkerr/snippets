import sys

def find_sol(index):
	if index == 0:
		return
	if data[index][2] + opt[p[index]] > opt[index - 1]:
		print(data[index])
		find_sol(p[index])
	else:
		find_sol(index - 1)


def bisect_right(left, right, target): #largest element smallest than/equal to target
	top = right
	while left <= right:
		mid = int((left + right)/2)
		if(target < data[mid][1]):
			if mid == 0:
				return -1
			else:
				right = mid - 1
				mid = right
		else:
			if mid == top:
				break
			elif(target >= data[mid][1]):
				left = mid + 1
				mid = left
			else:
				break
	return mid

data = [list(map(int, vector.split(' '))) for vector in open(sys.argv[1]).read().splitlines()]

n = len(data) + 1

data.sort(key = lambda x: x[1]) #sort by finish time

data.insert(0, [0, 0, 0]) #empty job to make things simpler

p = [0]

for index in range(1, n, 1):
	tmp = bisect_right(0, index - 1, data[index][0]) #cmp start to finish
	p.append(tmp)

#print(p)

opt = [0]

for index in range(1, n, 1):
	opt.append(max(data[index][2] + opt[p[index]], opt[index - 1]))

print(opt[n-1])

find_sol(n - 1)
	

