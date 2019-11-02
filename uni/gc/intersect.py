def det(a, b):
    return a[0] * b[1] - a[1] * b[0]

def line_intersection(line1, line2):
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0]) #[(a1, -a2) (b1, -b2)]
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1]) #[(a1, -a2) (b1, -b2)]

    div = det(xdiff, ydiff)
    if div == 0:
       raise Exception("lines do not intersect")

    d = (det(*line1), det(*line2))
    #these could fail
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div

    if x >= line[0][0] && x >= 
    if x

    return x, y

a1 = (0, 0)
a2 = (1, 1)

b1 = (4, 0)
b2 = (0, 4)
print(line_intersection((a1, a2), (b1, b2)))
