import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __lt__(self, other):
        if(self.x != other.x):
            return self.x < other.x
        return self.y < other.y;

    def __gt__(self, other):
        if(self.x != other.x):
            return self.x <= other.x
        return self.y <= other.y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def min(A, B):
        if(A.x != B.x):
            if(A.x <= B.x):
                return A
            return B
        if(A.y <= B.y):
            return A
        return B

    def max(A, B):
        if(A.x != B.x):
            if(A.x >= B.x):
                return A
            return B
        if(A.y >= B.y):
            return A
        return B

def cross_product(origin, A, B): #>0 left <0 right 0 colinear
    return (origin.x - A.x)*(origin.y - B.y) - (origin.y - A.y)*(origin.x - B.x)

def dist(p1, p2):
  	return (p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x)

A1 = Point(0, 1)
A2 = Point(0, 0)
A3 = Point(3, 0)
A4 = Point(2, 3)

x = cross_product(A2, A1, A3)

y = cross_product(A3, A2, A4)

w = cross_product(A4, A3, A1)

if((x > 0 and y > 0 and w > 0) or (x < 0 and y < 0 and w < 0)):
	print("conv")
else:
	print("not conv")

A21 = Point(A1.x - A2.x, A1.y - A2.y)

A23 = Point(A3.x - A2.x, A3.y - A2.y)

vA21 = dist(A2, A1)

vA23 = dist(A2, A3)

v = A21.x*A23.x + A21.y*A23.y

ca2 = v / (vA23*vA21)

A43 = Point(A3.x - A4.x, A3.y - A4.y)

A41 = Point(A1.x - A4.x, A1.y - A4.y)

vA43 = dist(A4, A3)

vA41 = dist(A4, A1)

v1 = A43.x*A41.x + A43.y*A41.y

ca4 = v1 / (vA43*vA41)

if(math.acos(ca2) + math.acos(ca4) > math.pi):
	print("int")
elif(math.acos(ca2) + math.acos(ca4) == math.pi):
	print("pe seg")
else:
	print("ext")



