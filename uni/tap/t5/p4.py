import sys
from queue import Queue

#used to compute best fractional knapsack solution starting from the current root
def bound(node, sack_weight, objects):
	if(node[3] >= sack_weight):
		return 0

	result = node[1]
	j = node[0] + 1

	total_weight = node[3]
	while(j < len(objects) and total_weight + objects[j][0] <= sack_weight):
		#we add as many full items as we can
		total_weight += objects[j][0]
		result += objects[j][1]
		j += 1

	#if theres still items left, add a part of the next one
	if(j < len(objects)):
		result += (sack_weight - total_weight) * objects[j][1] / objects[j][0]

	return result



def knapsack(sack_weight, objects):
	objects = sorted(objects, key = lambda x: x[1] / x[0], reverse = True)	#value per weight
	print(objects)

	q = Queue()								#level, profit, bound, weight

	v = [-1, 0, None, 0]					#root
	u = [-1, 0, None, 0]

	q.put(v)								#insert root into q

	max_profit = 0

	#standard BFS
	while(not q.empty()):
		v = list(q.get())

		#if we reached the end of the path, do nothing
		if(v[0] == len(objects) - 1):
			continue


		u[0] = v[0] + 1	#set u to a child of v (next level basically)

		#consider u as the child that includes the next item
		u[3] = v[3] + objects[u[0]][0]	#add weight of current level
		u[1] = v[1] + objects[u[0]][1]	#add value of current level

		#check if the current tree is better than the previous best
		if(u[3] <= sack_weight and u[1] > max_profit):
			max_profit = u[1]

		#add the current node to the queue if a solution is feasible
		u[2] = bound(u, sack_weight, objects)
		if(u[2] > max_profit):
			q.put(list(u))

		#consider u as the child that does not include the next item
		u[3] = v[3]
		u[1] = v[1]

		#add the current node to the queue if a solution is feasible
		if(v[2] > max_profit):
			u[2] = v[2]
			q.put(list(u))


	return max_profit







data = open(sys.argv[1]).read().splitlines()

sack_weight = int(data[0])
objects = [list(map(float, pair.split(' '))) for pair in data[1:]]	#weight, value

print(sack_weight, objects)

print(knapsack(sack_weight, objects))