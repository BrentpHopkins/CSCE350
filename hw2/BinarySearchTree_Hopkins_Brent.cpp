/**
 * @file Locker_Doors_Hopkins_Brent.cpp
 * @author Brent Hopkins
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022 Brent Peter Hopkins
 *
 */
#include <iostream>

using namespace std;
/**
 * @brief Binary search tree node
 *
 */
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int num)
    {
        data = num;
        left = NULL;
        right = NULL;
    }
};

/**
 * @brief Inserts the given data into the binary search tree
 *
 * @param root the root of the binary search tree
 * @param data  the data to be added to the binary search tree
 * @return Node* the root of the binary search tree
 */
Node *Insert(Node *root, int data)
{
    if (!root)
    {
        return new Node(data);
    }
    if (data > root->data)
    {
        root->right = Insert(root->right, data);
    }

    if (data < root->data)
    {
        root->left = Insert(root->left, data);
    }

    return root;
}; /**
    * @brief searches the for the given key in the binary search tree
    *
    * @param root the root of the binary search tree being searched
    * @param key the key being searched for
    * @return string a string containing each node visited and the results of the search
    */
string Search(Node *root, int key)
{
    string out = "";
    if (!root)
    {
        out.append(" Not Found\n");
        return out;
    }

    if (root->data == key)
    {
        out.append(to_string(root->data) + "\n");
        return out;
    }
    out.append(to_string(root->data) + ", ");

    if (root->data > key)
    {
        out.append(Search(root->left, key));
    }

    if (root->data < key)
    {
        out.append(Search(root->right, key));
    }
    return out;
}
/**
 * @brief finds the minimum value in the binary search tree
 *
 * @param root the root of the binary search tree
 * @return Node* the min value of the search tree
 */
Node *FindMinNode(Node *root)
{
    if (root->left)
    {
        return FindMinNode(root->left);
    }
    return root;
}

/**
 * @brief removes the node containing the given key from the binary search tree
 *
 * @param root the binary search tree from which the node is being removed
 * @param key the value to be removed
 * @return Node* the root of the binary search tree after the value has been removed
 */
Node *Delete(Node *root, int key)
{
    Node *min;
    if (!root)
    {
        return root;
    }

    if (root->data > key)
    {

        root->left = Delete(root->left, key);
    }
    else if (root->data < key)
    {
        root->right = Delete(root->right, key);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }

        if (root->right == NULL)
        {
            return root->left;
        }

        if (root->left == NULL)
        {
            return root->right;
        }

        min = FindMinNode(root->right);
        root->data = min->data;
        root->right = Delete(root->right, min->data);
    }
    return root;
}

int main()
{
    Node *root = NULL;
    bool run = true;
    int choice;
    int temp;
    while (run)
    {
        cout << "Pick an option" << endl;
        cout << "1:Add \n2:Delete \n3:Search \n4:Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "What int would you like to add" << endl;
            cin >> temp;
            root = Insert(root, temp);
            break;

        case 2:
            cout << "What int would you like to delete" << endl;
            cin >> temp;
            Delete(root, temp);
            break;

        case 3:
            cout << "What int would you like to search" << endl;
            cin >> temp;
            cout << Search(root, temp);
            break;

        case 4:
            run = false;
            break;

        default:
            break;
        }
    }

    return 0;
}