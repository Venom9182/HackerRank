def Reverse(head):
    x = None
    while head is not None:
        head.next, x, head = x, head, head.next
    return x
