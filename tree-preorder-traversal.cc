void Preorder(node *x) {
  stack<node*> s;
  for(;;) {
    while (x) {
      printf("%d ", x->data);
      if (x->right)
        s.push(x->right);
      x = x->left;
    }
    if (s.empty()) break;
    x = s.top();
    s.pop();
  }
}
