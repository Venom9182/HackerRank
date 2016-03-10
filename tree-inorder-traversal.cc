void Inorder(node *root) {
    if (root) {
        Inorder(root->left);
        printf("%d ", root->data);
        Inorder(root->right);
    }
}
