def print_m(matrix):
    for r in matrix:
        print(r)


def mergeRectSlices(s1, s2):
    out = []
    tmp = []

    for row1 in s1:
        s1rix1, s1riy1, s1rix2, s1riy2 = row1[0][0], row1[0][1], row1[1][0], row1[1][1]
        for row2 in s2:
            s2rjx1, s2rjy1, s2rjx2, s2rjy2 = row2[0][0], row2[0][1], row2[1][0], row2[1][1]

            # take highest y
            if int(s1riy2) > int(s2rjy2):
                tmp += [[[s1rix1, s1riy1], [s2rjx2, s2rjy2]]]
            else:
                tmp += [[[s1rix1, s1riy1], [s2rjx2, s1riy2]]]
    # no dup
    for elem in tmp:
        if elem not in out:
            if noPointInside(elem):
                out += [elem]

    return out


def noPointInside(rect):
    if len(rect) != 2:
        return False
    r1x1, r1y1, r1x2, r1y2 = rect[0][0], rect[0][1], rect[1][0], rect[1][1]
    for p in points:
        if int(r1x1) < int(p[0]) < int(r1x2):
            if int(p[1]) < int(r1y2):
                return False
    return True


# return 0 if a point is inside the rect
def area(rect):
    x1, y1, x2, y2 = int(rect[0][0]), int(rect[0][1]), int(rect[1][0]), int(rect[1][1])
    return abs(x2 - x1) * abs(y2 - y1)


l, h = input().strip(" ").split(" ")
n = int(input())

l = int(l)
h = int(h)

if n == 0:
    print(l * h)
    exit(1)

points = []
begin = [0, 0]
rectSlices = list([])

# build matrix, each row is composed of the two possible rectangle.
# [
#   [ [begin, point[i]], [begin, [point[i][0], h] ]
#   ....
# ]
for i in range(n):
    p = input().strip(" ").split(" ")
    points += [p]
    rectSlices += [[[begin, p]] + [[begin, [p[0], int(h)]]]]
    begin = [p[0], 0]

    # last one
    if i == n - 1:
        # if we haven't reached the limit
        if int(points[n - 1][0]) != int(l):
            rectSlices += [[[begin] + [[points[i][0], int(h)]]]]

# print("rectSlices:")
# print_m(rectSlices)
# print("=============")

# print("############")
area_max = 0
while len(rectSlices) > 1:
    # calc area for each round
    for row in rectSlices:
        for elem in row:
            tmp = area(elem)
            if tmp > area_max:
                area_max = tmp

    for i in range(0, len(rectSlices) - 1):
        rectSlices += [mergeRectSlices(rectSlices[i], rectSlices[i + 1])]

    # remove past rect
    for k in range(i + 2):
        rectSlices.pop(0)

    #print("rectSlices: ")
    #print_m(rectSlices)

print(area_max)
