void  merge(Node* root1, Node* root2)
{
    stack<Node*, int> s;
   
    Node* curr1 = root1;
    Node* curr2 = root2;

    while(1)
    {
        if(curr1 != NULL || curr2 != NULL)
        {
            if(curr1 == NULL)
            {
                s.push(make_pair(curr2, 2));
                curr2 = curr2->left;
            }
            else if(curr2 == NULL)
            {
                s.push(make_pair(curr1, 2));
                curr2 = curr2->left;
            }
            else
            {
                if(curr1->data < curr2->data)
                {
                    s.push(make_pair(curr2, 2));
                    curr2 = curr2->left;
                }
                else
                {
                    s.push(make_pair(curr1, 1));
                    curr1 = curr1->left;
                }
            }
        }
        else
        {
            if(s.empty() != true)
            {
                pair<Node*, int> temp = s.top();
                s.pop();

                if(temp.second == 1)
                {
                    curr1 = temp.first;
                    printf("%u ", curr->data);
                    curr1 = curr1->right;
                }
                else
                {
                    curr2 = temp.second;
                    printf("%u ", curr2->data);
                    curr2 = curr2->right;
                }
            }
            else
            {
                break;
            }
        }
    }
}
