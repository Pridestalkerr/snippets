import math

class punct:
    def __init__(self, a, b, name):
        self.x = a
        self.y = b
        self.id = name

def equal_points(A, B):
    if A.x is B.x and A.y is B.y:
        return True
    else:
        return False

def colinear(A, B, C):
    #check if area = 0
    if(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y) == 0):
        return True
    else:
        return False

def cross_product(origin, A, B): #>0 left <0 right 0 colinear
    return (origin.x - A.x)*(origin.y - B.y) - (origin.y - A.y)*(origin.x - B.x)

def convex_hull(points, hull):
    points.sort(key = lambda K:K.x)
    hull.append(points[0]) 
    points.pop(0); #remove leftmost element

    while():
        left_max = 0 #first element in order
        for index, point in enumerate(points):
            if(cross_product(hull[-1], points[left_max], point) > 0):
                left_max = point
            elif(cross_product(hull[-1], points[left_max], point) == 0):
                #pick furthest (add it to col points, not doing that here)


A1 = punct(0, 0, "A1")
A2 = punct(1, 0, "A2")
A3 = punct(0, 1, "A3")
A4 = punct(1, 1, "A4")

if(colinear(A1, A2, A3) and colinear(A2, A3, A4)):
    #segment, check order
else:
    #we convex hull and check whether we have 3 or 4 points
    points = [A1, A2, A3, A4]

    hull = []

    convex_hull(points, hull)

    if(len(hull) == 3):
        #triangle
    elif(len(hull) == 4):
        #square
    #anything else means some points are equal and therefore segment