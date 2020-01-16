import sys
import math
import random
import matplotlib.pyplot as plt



class Individual:
	def __init__(self, cromosome, genome, fitness, sel_prob):
		self.cromosome = cromosome
		self.genome = genome
		self.fitness = fitness
		self.sel_prob = sel_prob

	def __repr__(self):
		return "x: " + str(self.cromosome) + ", f: " + str(self.fitness) + ", selection prob: " + str(self.sel_prob) + '\n'

#-x^2 + x + 2
def func1(x):
	return -(x*x) + x + 2


def fitness(cromosome, domain, genome_len):
	x = (domain[1] - domain[0]) / (2**genome_len - 1) * cromosome + domain[0]	#actual coordinate
	return func1(x)


#returns smallest element bigger than/equal to target
def bisect_left(array, left, right, target):	#left, right inclusive
	top = left
	while left <= right:
		mid = int((left + right)/2)
		if(target > array[mid]):
			if mid == 0:
				return -1
			else:
				left = mid + 1
				mid = left
		else:
			if mid == left:
				break
			elif(target <= array[mid]):
				right = mid - 1
				mid = right
			else:
				break
	return mid


def selection(population, C):

	#make sure to add min to all values from now on
	#calculate fitness_sum
	fitness_sum = 0
	for individual in population:
		fitness_sum += individual.fitness - C


	#calculate probabilities as well as an array of sums for them
	prob_sums = [0]
	for individual in population:
		individual.sel_prob = (individual.fitness - C) / fitness_sum
		# print(individual)
		prob_sums.append(prob_sums[-1] + individual.sel_prob)

	# print(sum(i.sel_prob for i in population))
	# print(prob_sums)


	#proportional selection
	selected = []
	for itr in range(len(population)):
		#roulette
		u = random.uniform(0, 1)	#depending on rounding this should be [0, 1)
		chosen = bisect_left(prob_sums, 0, len(population), u)	#pop_size cause we also have 0 at the beginning
		# print(">>>>>", population[chosen - 1])
		selected.append(population[chosen - 1])		#currently no need for a copy

	return selected


def swap_genome(a, b):
	split_point = random.randint(0, len(a.genome) - 1)
	a.genome[:split_point], b.genome[:split_point] = b.genome[:split_point], a.genome[:split_point]

	value = 0
	for bit in a.genome:
		value = (value << 1) | bit
	a.crossover = value

	value = 0
	for bit in b.genome:
		value = (value << 1) | bit
	b.crossover = value


def crossover(population, cross_prob):
	prev_individual = None
	for individual in population:
		u = random.uniform(0, 1)
		if(1):
			if(prev_individual == None):
				prev_individual = individual
			else:
				swap_genome(prev_individual, individual)
				prev_individual = None


def mutation(population, mut_prob):
	for individual in population:
		u = random.uniform(0, 1)
		if(u < mut_prob):
			pos = random.randint(0, len(individual.genome) - 1)
			False if individual.genome[pos] == True else True
			value = 0
			for bit in individual.genome:
				value = (value << 1) | bit
			individual.crossover = value



def main():
	data = open(sys.argv[1], 'r').read().splitlines()

	pop_size = int(data[0])
	domain = [int(val) for val in data[1].split(' ')]
	precision = int(data[2])
	cross_prob = float(data[3])
	mut_prob = float(data[4])
	generations = int(data[5])


	#calculate cromosome size
	genome_len = math.ceil(math.log( (domain[1] - domain[0]) * (10**precision) ))


	#generate random 1st generation
	population = [Individual(0, [False] * genome_len, 0, 0) for _ in range(pop_size)]

	min_fitness = 0	#lets save the most garbage individual as well
	for individual in population:
		individual.cromosome = random.getrandbits(genome_len)	#generate random cromosome

		bits = individual.cromosome
		for i in range(genome_len):
			individual.genome[i] = bool(bits % 2)
			bits //= 2

		individual.fitness = fitness(individual.cromosome, domain, genome_len)				#calculate its fitness

		if(individual.fitness < min_fitness):
			min_fitness = individual.fitness

	first = 1
	for generation in range(generations):
		if(first == 1):
			#heavy print
			population = selection(population, min_fitness)

			print(population)

			crossover(population, cross_prob)

			mutation(population, mut_prob)

			#after were finished
			min_fitness = 0	#reset the poor guy
			for individual in population:
				if(individual.fitness < min_fitness):
					min_fitness = individual.fitness

			first = 0

		else:
			avg = sum(fitness(individual.cromosome, domain, genome_len) for individual in population) / pop_size
			print("avg: ", avg)	#this is worthless because of fp arithmetic
			plt.plot([generation], [avg], marker='o', markersize=3, color="red")

			print("max: ", fitness(max(population, key = lambda individual : fitness(individual.cromosome, domain, genome_len)).cromosome, domain, genome_len), '\n')

			population = selection(population, min_fitness)

			crossover(population, cross_prob)

			mutation(population, mut_prob)

			#after were finished
			min_fitness = 0	#reset the poor guy
			for individual in population:
				if(individual.fitness < min_fitness):
					min_fitness = individual.fitness



	plt.ylabel('average value')
	plt.xlabel('generation')
	plt.show()



if(__name__ == "__main__"):
	main()