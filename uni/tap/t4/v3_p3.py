import sys


def max_size(board, k):
	n = len(board)
	m = len(board[0])

#computation:
#	for each cell, keep a counter of how big a square can be made using that cell as top-left
#	all 'wall' cells will have 0 as count (obviously)
#	reverse iterate the matrix as to avoid recursioun, god bless iteration
#	scan algorithm explained inside the loop

	counts = [ [0]*m for i in range(n) ]
	for i in reversed(range(n)):
		for j in reversed(range(m)):
			#if the cell is a 'wall' assign 0 to its counter
			if board[i][j] == 0:
				#current cell is not a 'wall' cell
				if i < (n - 1) and j < (m - 1):
					#for all other cells, check the count of the cell on its right, right-below, and below. Take the min of them and add 1 and assign that to its counter
					counts[i][j] = (1 + min(counts[i][j+1], counts[i+1][j], counts[i+1][j+1]))
				else:
					#if the current cell is an edge cell (bottom or right edge only) assign 1 to its counter
					counts[i][j] = 1;

	print(sum(sum(1 for element in row if element >= k) for row in counts)) #for task 2, just count how many squares you managed to compute that are larger than k

#solution:
#	maximum value in counts, print its indexes as well if youre interested in its position

	return max(max(row) for row in counts)


board = [list(map(int, vector.split(' '))) for vector in open(sys.argv[1]).read().splitlines()]

n = board[0][0]
m = board[0][1]
board.pop(0)

k = board[n][0]
board.pop(n)


print(max_size(board, k))

