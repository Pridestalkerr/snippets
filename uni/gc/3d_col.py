def col(p1, p2, p3): #x, y, z
	p1p2 = [p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]]
	p1p3 = [p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]]

	sol = [p1p2[1]*p1p3[2] - p1p2[2]*p1p3[1], p1p2[2]*p1p3[0] - p1p2[0]*p1p3[2], p1p2[0]*p1p3[1] - p1p2[1]*p1p3[0]] #i,j,k

	if(sol == [0, 0, 0]):
		print("col")
	else:
		print("not col")

col([1,1,1], [2,2,2], [3,3,4])
