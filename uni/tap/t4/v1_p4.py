import sys

#this is recursive, complexity is identic to iteration method (!), can be unpacked to an iterative version fairly easily
#fun(n, k) = true if we can build a new array of size = n, such that its elements sum to k and new_array[i] was taken from the i-th array
#since we have n total arrays, and we're interested in making the solution sum to k, there are only n*k possible fun() calls, cache their values so you dont recompute them
#computation:
#	start with fun(n, k)
#		for element in n-th array
#			compute fun(n, k - element)
#
#this is a DFS, so the program will finish as soon as it finds a solution (compared with the iterative method which should always compute the whole problem)
def fun(n, k):
	if(n == 0):
		for element in data[0]:
			if(k - element == 0):
				fun_values[0][k] = True
				return True
			else:
				fun_values[0][k] = False
	else:
		for element in data[n]:
			if(k - element > 0):
				if(fun_values[n - 1][k - element] == True or (fun_values[n - 1][k - element] == None and fun(n - 1, k - element))):
					fun_values[n][k] = True
					return True

	fun_values[n][k] = False
	return False




data = [list(map(int, vector.split(' '))) for vector in open(sys.argv[1]).read().splitlines()]

n = data[0][0]
k = data[0][1]

fun_values = [ [None]*(k+1) for i in range(n) ]

data.pop(0)

if(fun(n - 1, k)):
	n-=1
	while(n >= 0):
		if(n == 0):
			break
		for elm in data[n]:
			if(fun(n-1, k - elm)):
				print(elm)
				k -= elm
				n -= 1
				break

	print(k)

else:
	print("no solution")