def GetNode(x, position):
    y = x
    for i in range(position+1):
        y = y.next
    while y is not None:
        x, y = x.next, y.next
    return x.data
