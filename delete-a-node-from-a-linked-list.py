def Delete(head, position):
    if position == 0:
        return head.next
    x = head
    for i in range(position-1):
        x = x.next
    x.next = x.next.next
    return head
