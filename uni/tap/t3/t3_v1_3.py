import sys

#quick explanation:
#	https://leetcode.com/problems/median-of-two-sorted-arrays/solution/

def median(n_arr, m_arr):

	if(len(n_arr) > len(m_arr)):
		n_arr, m_arr = m_arr, n_arr
	n = len(n_arr)
	m = len(m_arr)
	left = 0
	right = n

	while(left <= right):
		i = int((left + right) / 2)
		j = int((n + m + 1) / 2) - i

		if(i < n and j > 0 and m_arr[j - 1] > n_arr[i]):
			left = i + 1
		elif(i > 0 and j < m and m_arr[j] < n_arr[i - 1]):
			right = i - 1
		else:
			if(i == 0):
				median = m_arr[j - 1]
			elif(j == 0):
				median = n_arr[i - 1]
			else:
				median = max(n_arr[i - 1], m_arr[j - 1])
			break

	if((n + m) % 2 == 1):
		return median

	if(i == n):
		return (median + m_arr[j]) / 2.0

	if(j == m):
		return (median + n_arr[i]) / 2.0

	return (median + min(n_arr[i], m_arr[j])) / 2.0



data = open(sys.argv[1], 'r').read().splitlines()

n = int(data[0])

n_arr = [int(itr) for itr in data[1].split(' ')]

m = int(data[2])

m_arr = [int(itr) for itr in data[3].split(' ')]

print(median(n_arr, m_arr))