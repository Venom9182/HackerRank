void Postorder(node *x) {
  stack<node*> s;
  for(;;) {
    while (x) {
      s.push(x);
      x = x->left;
    }
    while (! s.empty() && s.top()->right == x) {
      x = s.top();
      s.pop();
      printf("%d ", x->data);
    }
    if (s.empty()) break;
    x = s.top()->right;
  }
}
