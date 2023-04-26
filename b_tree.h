#pragma once
#include "song.h"

/*
Pseudocode sources used as guide for implementation:
https://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture17.html
https://gist.github.com/nlowe/6e2bf999d53b2bb31321d30aafdd510a
*/

class B_Tree;
class Node;

class Node
{
    friend class B_Tree;

    B_Tree* tree;
    int num_keys;
    bool is_leaf;

    Song* keys; // An array will contain the keys
    Node** children; // An array will contain pointers to the children nodes

    public:
        Node(bool is_leaf, B_Tree* tree);
        void split_child(int child_idx);
        void insert_non_full(Song k);
};

class B_Tree
{
    friend class Node;

    int l; // Half of the maximum number of children
    Node* root;

    void print_tree_helper(Node* n);
    void destructor_helper(Node* n);
    Song* search_helper(Node* n, string search_name);

    public: 
        int num_nodes; // Number of nodes
        B_Tree(int l);
        ~B_Tree();
        void insert_key(Song k);
        void print_tree(); // Inorder traversal of B tree
        Song* search(string search_name);
};

B_Tree::B_Tree(int l)
{
    this->l = l;
    this->num_nodes = 1;
    // A single root node is a leaf by default
    this->root = new Node(true, this);
}

Node::Node(bool i_l, B_Tree* tree)
{
    this->is_leaf = i_l;
    this->num_keys = 0;
    this->tree = tree;
    this->keys = new Song[2*tree->l-1];
    this->children = new Node*[2*tree->l];
}

void Node::split_child(int child_idx)
{
    Node* y = this->children[child_idx-1];
    Node* z = new Node(y->is_leaf, this->tree);

    int t = (z->tree->l);

    // Since node y was full, node z must have t-1 keys
    z->num_keys = t-1;

    // Copy right half of node y's keys into node z
    for(int i = 1; i <= t-1; i++)
    {
        z->keys[(i)-1] = y->keys[(i+t)-1];
    }

    // If node y is not a leaf, copy over the right half of the children of y into z
    if(!y->is_leaf)
    {
        for(int i = 1; i <= t; i++)
        {
            z->children[(i)-1] = y->children[(i+t)-1];
        }
    }

    // Node y now has t-1 keys
    y->num_keys = t-1;

    // Shift all the children in the parent node over from i+1, then add the new child into node x
    // Node y will half its number of keys as the ith child of x and node z will contain the other half of the keys
    for(int i = this->num_keys+1; i >= child_idx+1; i--)
    {
        this->children[(i+1)-1] = this->children[(i)-1];
    }
    this->children[(child_idx+1)-1] = z;

    // Keys will also have to be shifted over
    for(int i = this->num_keys; i >= child_idx; i--)
    {
        this->keys[(i+1)-1] = this->keys[(i)-1];
    }

    // Accomodate the new key brought in from the middle of node y back into node x
    this->keys[(child_idx)-1] = y->keys[(t)-1];
    this->num_keys++;

    // Increment the number of nodes
    this->tree->num_nodes++;
}

void Node::insert_non_full(Song k)
{
    int i = this->num_keys; // Set i to the number of keys in the node

    // If the node is a leaf
    if(this->is_leaf) 
    {
        // Consider replacing this by inserting into a multiset

        // This loop determines where in the key vector the key k needs to be placed
        while(i >= 1 && k < this->keys[(i)-1]) // While the number of keys in the node >= 1 AND the key k is less than the last key of the node
        {
            this->keys[(i+1)-1] = this->keys[(i)-1]; // Set 
            i--;
        }

        // Set the key at index i to k
        this->keys[(i+1)-1] = k;

        // Increment the number of keys
        this->num_keys++;
    }
    // Otherwise, if the node is not a leaf
    else
    {
        // While the number of keys in the node >= 1 AND the key k is less than the last key of the node
        while(i >= 1 && k < this->keys[(i)-1]) 
        {
            i--;
        }
        i++;
        // If the ith child is full
        if(this->children[(i)-1]->num_keys == (2*(this->tree->l)-1)) 
        {
            //cout << "Split at node" << endl;
            this->split_child(i); // Split the ith child
            if(k > this->keys[(i)-1]) // If key k is greater than the ith key
            {
                i++; // Increment i
            }
        }
        // Insert the key k into the non-full ith child
        this->children[(i)-1]->insert_non_full(k);
    }

}

void B_Tree::insert_key(Song k)
{
    // If root is empty (which could only happen when tree is empty)
    if(root->num_keys == 0)
    {
        // Insert key into the root node as the 0th key
        root->keys[0] = k;

        // Set the number of keys in the root to 1
        root->num_keys = 1;
    }
    // Otherwise, the root is not empty (meaning the tree is not empty)
    else
    {
        // If the root node is full, it needs to be split, so create a new root node with the old root node as its 0th and only child
        if(root->num_keys == 2*l-1)
        {
            Node* old_root = root;
            root = new Node(false, this); // The new root will not be a leaf
            root->children[0] = old_root;
            num_nodes++;

            // Split the old root's child
            //cout << "Split at root" << endl;
            root->split_child(1); // The child index will be 0 (1 in one-based indexing) given that it only has one child

            // After split, insert the key regularly as there is now space in the tree
            root->insert_non_full(k);
        }

        // Otherwise, no splitting needs to be done
        else
        {
            root->insert_non_full(k);
        }
    }

    //cout << "Current number of nodes: " << this->num_nodes << endl;
}

void B_Tree::print_tree()
{
    print_tree_helper(root);
}

void B_Tree::print_tree_helper(Node* n)
{
    if(n->is_leaf)
    {
        for(int i = 0; i < n->num_keys; i++)
        {
            cout << n->keys[i].name << endl;
        }
    }
    else
    {
        for(int i = 0; i < n->num_keys; i++)
        {
            print_tree_helper(n->children[i]);
            cout << n->keys[i].name << endl;
        }
        print_tree_helper(n->children[n->num_keys]);
    }
}

B_Tree::~B_Tree()
{
    destructor_helper(root);
}

void B_Tree::destructor_helper(Node* n)
{
    if(n->is_leaf)
    {
        delete[] n->keys;
        delete[] n->children;
    }
    else
    {
        for(int i = 0; i <= n->num_keys; i++)
        {
            destructor_helper(n->children[i]);
        }

        delete[] n->keys;
        delete[] n->children;
    }
}

Song* B_Tree::search(string search_name)
{
    return search_helper(this->root, search_name);
}

Song* B_Tree::search_helper(Node* n, string search_name)
{
    int i = 1;

    // Determine which key/child should be searched for the name
    while(i <= n->num_keys && search_name > n->keys[(i)-1].name)
    {
        // Increment i until it gets to the point where the song object may lie in the tree
        i++;
    }
    if(i <= n->num_keys && search_name == n->keys[(i)-1].name)
    {
        // If the song with the searched name was found, return a pointer to the song object
        return &(n->keys[(i)-1]);
    }
    else if(n->is_leaf)
    {
        // If the node is a leaf, return nullptr meaning it was not found
        return nullptr;
    }
    else
    {
        // Otherwise, search the ith child
        return search_helper(n->children[(i)-1], search_name);
    }
}