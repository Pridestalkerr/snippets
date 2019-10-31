import sys
import functools

def tuple_comp(a, b):
	if(a[0] < b[0]):
		return -1
	if(a[0] > b[0]):
		return 1
	#==
	if(a[1] < b[1]):
		return -1
	if(a[1] > b[1]):
		return 1

	return 0

def tuple_key(x):
	return int(str(x[0]) + str(x[1]))

def main():

	intervals = []

	data = open(sys.argv[1], 'r').read().splitlines()

	a = int(data[0].split(' ')[0])
	b = int(data[0].split(' ')[1])

	n = int(data[1])

	for itr in range(2, n+2): #2->8
		ai = int(data[itr].split(' ')[0])
		bi = int(data[itr].split(' ')[1])
		if(ai != bi):
			intervals.append((ai, bi)) #tuples

	intervals.sort(key = functools.cmp_to_key(tuple_comp)) #based on timsort (nlogn time)
	print(intervals)	

	lead = (a - 1, a - 1)
	solution = []

	for interval in intervals:
		if(interval[0] <= a):
			if(interval[1] > lead[1] and interval[1] > a): #could be useless 
				lead = interval
				if(interval[1] >= b):
					break
		else:
			if(lead[1] <= a):
				print(-1)
				return
			else:
				solution.append(lead)
				a = lead[1]
				lead = (a - 1, a - 1)

	if(lead[1] >= b):
		solution.append(lead)
		print(solution)
	else:
		print(-1)

	test = [[0] * 1001] * 1001
	test[1000][1000] = 2


main()

