import sys


def str_to_int(string):
	return (ord(string[0]) - 97) + (ord(string[1]) - 97)*25

def int_to_str(integer):
	return chr(integer%25 + 97) + chr(int(integer/25 + 97))


words = open(sys.argv[1], 'r').read().splitlines()[0].split(' ')

#computation:
#	maxlen[ words[i][-2] ] = size of the largest sequence of viable words such that the last word ends with words[i][-2] (2 certain letters) => 
#	=> hash alpha strings of len = 2 to int => 26*26 = 676 possible combinations/indexes

maxlen = [0] * 676 #store the max word as well if you want traceback**

#formula: 
#	maxlen[ words[i][-2] ] = max(maxlen[ words[i][-2] ], maxlen[ words[i][0] ] + 1) 

for word in words:
	maxlen[str_to_int(word[-2:])] = max(maxlen[str_to_int(word[-2:])], maxlen[str_to_int(word[:2])] + 1)

#solution:
#	maximum value in maxlen

print(int_to_str(max(range(len(maxlen)), key = maxlen.__getitem__)), max(maxlen))

#traceback:
#	keep in mind (**)
#	(1) after finding the solution from above and printing solution.full_word 
#		string_to_int(solution.full_word[-2]) = new_index => maxlen[new_index] will be the previous word in the sequence
#		print maxlen[new_index].word
#		goto (1) using maxlen[new_index] as solution