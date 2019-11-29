import sys

#traceback function
def find_sol(index):
	if index == 0:
		return
	if data[index][2] + opt[p[index]] > opt[index - 1]:
		print(data[index])
		find_sol(p[index])
	else:
		find_sol(index - 1)

#returns largest element smallest than/equal to target
def bisect_right(left, right, target):
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


#computation:
#	sort jobs by finish time
#	have a look up array, p[i] = largest j < i such that jobs[j] compatible with jobs[i]
#	store the upcoming subproblems in an array, opt[]
#	opt[i] = best total weight usign the first i jobs
#	formula for opt[i]:
#		opt[i] = max(jobs[i].weight + opt[p[i]], opt[i - 1])
#
#	generating opt from i = 1 -> n iteratively will be fine

data = [list(map(int, vector.split(' '))) for vector in open(sys.argv[1]).read().splitlines()]

n = len(data) + 1

data.sort(key = lambda x: x[1]) #sort by finish time

data.insert(0, [0, 0, 0]) #empty job to make things simpler

p = [0]

#compute p, O(n*logn)
for index in range(1, n, 1):
	tmp = bisect_right(0, index - 1, data[index][0]) #cmp start to finish
	p.append(tmp)

opt = [0]

#calculate subproblems
for index in range(1, n, 1):
	opt.append(max(data[index][2] + opt[p[index]], opt[index - 1]))

#solution:
#	will be the last element of opt

print(opt[n-1])

#traceback:
#	all you have to do is start at the solution and walk up the generated subproblem tree using the previous stated formula for opt[i]

find_sol(n - 1)
	

