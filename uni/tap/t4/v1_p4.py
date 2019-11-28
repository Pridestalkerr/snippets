import sys

def fun(n, k): #fun(n,k) = true daca putem forma un nou vector de dim=n a.i suma = k
	#print(k)
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

print(fun(n - 1, k))



