// Merge two sorted linked lists
def MergeLists(a, b):
    h, t = None, None
    while a is not None and b is not None:
        if a.data < b.data:
            if h is None:
                h = t = a
            else:
                t.next = a
                t = t.next
            a = a.next
        else:
            if h is None:
                h = t = b
            else:
                t.next = b
                t = t.next
            b = b.next
    if h is None:
        h = b if a is None else a
    else:
        t.next = b if a is None else a
    return h
