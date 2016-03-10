def Insert(head, data):
    if head is None:
        return Node(data)
    x = head
    while x.next is not None:
        x = x.next
    x.next = Node(data)
    return head
