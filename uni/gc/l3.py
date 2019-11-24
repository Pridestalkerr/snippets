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


def line_intersection(A, B, C, D):
    a1 = A.y - B.y
    a2 = C.y - D.y
    b1 = B.x - A.x
    b2 = D.x - C.x
    c1 = B.x*A.y - A.x*B.y
    c2 = D.x*C.y - C.x*D.y

    det = a1*b2 - b1*a2

    if(det != 0):
        x = ((B.x*A.y - A.x*B.y)*b2 - (D.x*C.y - C.x*D.y)*b1) / det;
        y = ((D.x*C.y - C.x*D.y)*a1 - (B.x*A.y - A.x*B.y)*a2) / det;
        if(x < min(A.x, B.x) or x < min(C.x, D.x) or x > max(A.x, B.x) or x > max(C.x, D.x)):
            print("no intersection")
        else:
            print(x, y)

    elif(b1*c2 - b2*c1 != 0):
        print("no intersection")

    elif(a1*c2 - a2*c1 != 0):
        print("no intersection")

    else:
        #coliniare
        min1 = Point.min(A, B)
        min2 = Point.min(C, D)
        max1 = Point.max(A, B)
        max2 = Point.max(C, D)

        if(min1 == min2 and max1 == max2):
            print("==")

        elif(max2 < min1):
            print("no intersection")

        elif(max2 == min1):
            print(min1.x, min1.y)

        elif(min2 < min1):
            print(min1.x, min1.y, min(max1,max2).x, min(max1, max2).y)

        elif(min1 == min2 and min2 == min(max1, max2)):
            print(min1.x, min1.y)

        elif(min2 < min(max1, max2)):
            print(min2.x, min2.y, min(max1,max2).x, min(max1, max2).y)

        elif(min2 == min(max1, max2)):
            print(min2.x, min2.y)

        else:
            print("no intersection")


a1 = Point(0, 0)
a2 = Point(2, 2)

b1 = Point(3, 3)
b2 = Point(1, 1)

line_intersection(a1, a2, b1, b2)
