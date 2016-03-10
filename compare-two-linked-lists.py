def CompareLists(headA, headB):
    while headA is not None and headB is not None:
        if headA.data != headB.data:
            return 0
        headA, headB = headA.next, headB.next
    return 1 if headA is None and headB is None else 0
