def ReversePrint(head):
    x = None
    while head is not None:
        head.next, x, head = x, head, head.next
    while x is not None:
        print(x.data)
        x = x.next
