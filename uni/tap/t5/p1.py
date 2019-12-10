import sys

#and = a, or = o
#k variables
#x1,2,3...k
#expression
#!1o1o2o!3a...

data = open(sys.argv[1]).read().splitlines()

var_count = int(data[0])
expression = data[1]

variables = [0] * var_count

print(var_count, expression, variables)

def bt():
	print(1)



bt()

