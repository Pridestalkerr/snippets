import sys


def str_to_int(string):
	return (ord(string[0]) - 97) + (ord(string[1]) - 97)*25

def int_to_str(integer):
	return chr(integer%25 + 97) + chr(int(integer/25 + 97))


words = open(sys.argv[1], 'r').read().splitlines()[0].split(' ') #goddamn null

maxlen = [0] * 676

for word in words:
	maxlen[str_to_int(word[-2:])] = max(maxlen[str_to_int(word[-2:])], maxlen[str_to_int(word[:2])] + 1)

print(int_to_str(max(range(len(maxlen)), key = maxlen.__getitem__)), max(maxlen)

