import sys

def main():

	data = open(sys.argv[1], 'r').read().splitlines()

	n = int(data[0])

	array = [int(itr) for itr in data[1].split(' ')]

	#we'll use binary search (O(logn))
	left = 0
	right = n - 1
	while(left <= right):
		m = int((left + right - 1) / 2)

		if(array[m] == m):
			print(m)
			return 0

		if(array[m] < m):
			#go right
			left = m + 1
		else:
			#go left
			right = m + 1

	return 0

main()