Node* RemoveDuplicates(Node *head)
{
  for (auto p = head; p; p = p->next) {
    auto q = p->next;
    while (q && q->data == p->data) {
      p->next = q->next;
      delete q;
      q = p->next;
    }
  }
  return head;
}
