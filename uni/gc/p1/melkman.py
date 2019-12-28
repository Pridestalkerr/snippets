
from collections import deque

class Point:
    def __init__(self, a, b):
        self.x = a
        self.y = b

    def __init__(self, a):
    	self.x = a[0]
    	self.y = a[1]

    def __str__(self):
    	return '(' + str(self.x) + ', ' + str(self.y) + ')'


def cross_product_sign(a, b, c):
    if((b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y) >= 0):
        return True		#to the right
    else:
        return False	#to the left (or collinear)


def do_melkman(polyline):
	if(len(polyline) < 3):
		return list(polyline);	#less than 3 points, return a copy

	dq = deque()

	if(cross_product_sign(polyline[0], polyline[1], polyline[2])):
		#right
		dq.append(polyline[0])
		dq.append(polyline[1])
	else:
		#left
		dq.appendleft(polyline[0])
		dq.appendleft(polyline[1])

	dq.append(polyline[2])
	dq.appendleft(polyline[2])

	if(len(polyline) == 3):
		return list(dq)

	itr = 3
	while(itr < len(polyline)):
		while(cross_product_sign(polyline[itr], dq[0], dq[1]) and cross_product_sign(dq[-2], dq[-1], polyline[itr])):
			itr += 1
			if(itr > len(polyline) - 1):
				return list(dq)

		while(not cross_product_sign(dq[-2], dq[-1], polyline[itr])):
			dq.pop()

		dq.append(polyline[itr])

		while(not cross_product_sign(polyline[itr], dq[0], dq[1])):
			dq.popleft()

		dq.appendleft(polyline[itr])
		itr += 1

	return list(dq)



