struct node
{
    int x;
    node *next;
};

node *head = NULL;

void Addfirst(int x)
{
    node *nn = new node;
    nn->x = x;
    nn->next = head;
    head = nn;
}

int delfirst()
{
    if (head == NULL)
        return -1;
    node *nn = head;
    head = head->next;
    delete nn;
    return 0;
}

int delete_key(int x)
{
    node *curr = head;
    node *prev = NULL;
    int a;
    while (curr != NULL)
    {
        a = curr->x;
        if (a == x)
        {
            if (curr == head)
            {
                head = head->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return -1;
}

void search(int x)
{
    node *curr = head;
    int a;
    while (curr != NULL)
    {
        a = curr->x;
        if (a == x)
        {
            cout << "True" << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "False" << endl;
}

int length()
{
    node *curr = head;
    int count = 0;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}