import sys


def max_size(board, k):
	n = len(board)
	m = len(board[0])

	counts = [ [0]*m for i in range(n) ]
	for i in reversed(range(n)):     # for each row
		for j in reversed(range(m)): # for each element in the row
			if board[i][j] == 0:
				if i < (n - 1) and j < (m - 1):
					counts[i][j] = (1 + min(counts[i][j+1], counts[i+1][j], counts[i+1][j+1]))
				else:
					counts[i][j] = 1;

	print(sum(sum(1 for element in row if element >= k) for row in counts))

	return max(max(row) for row in counts)


board = [list(map(int, vector.split(' '))) for vector in open(sys.argv[1]).read().splitlines()]

n = board[0][0]
m = board[0][1]
board.pop(0)

k = board[n][0]
board.pop(n)


print(max_size(board, k))

