def InsertNth(head, data, position):
    if position == 0:
        return Node(data, head)
    x = head
    for _ in range(position-1):
        x = x.next
    x.next = Node(data, x.next)
    return head
