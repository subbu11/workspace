
void reverseLevel(Node* root)
{
    if(root == NULL)
        return;
    queue<Node*> q;

    while(root)
    {
        q.push(root);
        if(root->left)
            q.push(root->left);
        if(root->right)
            q.push(root->right);
    }
}
