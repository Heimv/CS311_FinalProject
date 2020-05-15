// CS311 : This is the BST implementation file template by Rika Yoshii

// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.  Couts are there to test to make sure
// you set the Up links correctly!!!! (Fall 19)
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// Try not to delete the ** comments, but add the code next to them
// Make sure all { } match. Doing Tab on each line helps.
// Draw pictures as you complete each **

// =========================================================
//HW#: HW4 BST
//Your name: Victor Heim
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================

#include <iostream>
#include "binstree.h"

using namespace std;

// constructor  initializes Root
BST::BST() {
    Root = nullptr;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST() {
    dTraverse(Root); // traverse to delete all vertices in post order
    Root = nullptr;
}

// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dTraverse(Vertex *V) { // recursive post order traversal
    if (V != nullptr) {
        dTraverse(V->Left);         // destroy left sub tree of V
        dTraverse(V->Right);//  destroy right sub tree of V
        cerr << "Deleting Elem with Id: " << V->Elem->Id << endl;
        free(V->Elem);
        V->Elem = nullptr;
        if (V->Up == nullptr)
            Root = nullptr;
        free(V);

    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display(DisplayType dType) {
    switch (dType) {
        case INORDER:
            cout << "Elements in the IN order: " << endl;
            InOrderTraversal(Root, nullptr);  // start in-order traversal from the root
            break;
        case GRAPHICAL:
            cout << "Element in the graphical form: " << endl;
            printTree(Root, nullptr, false);
            break;
        default:
            cout << "Elements in the IN order: " << endl;
            InOrderTraversal(Root, nullptr);  // start in-order traversal from the root
            break;
    }
}

// Helper function to print branches of the binary tree
void BST::showTrunks(Trunk *p) {
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void BST::printTree(Vertex *root, Trunk *prev, bool isLeft) {
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->Left, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft) {
        trunk->str = ".---";
        prev_str = "   |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->Elem << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->Right, trunk, false);
}

// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 
void BST::InOrderTraversal(Vertex *V, std::vector<Elem_t *> *vect) {
    if (V != nullptr) {
        InOrderTraversal(V->Left, vect);
        // ** traverse left sub-tree of V recursively
        // ** display V's element, height and balance and do endl;
        // ** traverse right sub-tree of V
        if (vect != nullptr)
            vect->push_back(new Elem_t(*(V->Elem)));
        InOrderTraversal(V->Right, vect);
    }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
Elem_t *BST::Search(Elem_t *K) {
    Vertex *tmp = new Vertex();

    PreOrderSearch(Root, K, tmp, nullptr);
    return tmp->Elem;  // start pre-order traversal from the root
}

std::vector<Elem_t *> *BST::Search(int id) {
    std::vector<Elem_t *> *tmp = new std::vector<Elem_t *>();
    Elem_t *tmpElem = new Elem_t(id, this);

    PreOrderSearch(Root, tmpElem, nullptr, tmp);
    return tmp;
}

std::vector<Elem_t *> *BST::Search(Elem_t::importance importance) {
    Elem_t *tmpElem = new Elem_t(importance, this);
    std::vector<Elem_t *> *tmp = new std::vector<Elem_t *>();

    PreOrderSearch(Root, tmpElem, nullptr, tmp);
    return tmp;
}

std::vector<Elem_t *> *BST::Search(std::string toSearch) {
    Elem_t *tmpElem = new Elem_t(toSearch, this);
    std::vector<Elem_t *> *tmp = new std::vector<Elem_t *>();

    PreOrderSearch(Root, tmpElem, nullptr, tmp);
    return tmp;
}

std::vector<Elem_t *> *BST::Search(bool done) {
    Elem_t *tmpElem = new Elem_t(done, this);
    std::vector<Elem_t *> *tmp = new std::vector<Elem_t *>();

    PreOrderSearch(Root, tmpElem, nullptr, tmp);
    return tmp;
}

// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PreOrderSearch(Vertex *V, Elem_t *K, Vertex *elem, std::vector<Elem_t *> *currentSearch) {
    if (V == nullptr)
        return false;
    else if (*K == *(V->Elem)) {
        if (elem != nullptr) {
            elem = V;
            return true;
        } else if (currentSearch != nullptr) {
            currentSearch->push_back(V->Elem);
        }
    }
    return (PreOrderSearch(V->Left, K, elem, currentSearch) ^
            PreOrderSearch(V->Right, K, elem, currentSearch)); //** traverse right sub-tree of V recursively
}

// ------ The following are for adding and deleting vertices -----

// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(Elem_t *E) {
    // Set up a new vertex first
    Vertex *N = new Vertex; // N will point to the newly created vertex
    N->Left = nullptr;   // make sure it does not
    N->Right = nullptr;   // point to anything
    N->Elem = E;      // put element E in it
    N->Height = 0;
    N->Balance = 0;
    N->Up = nullptr;      // no parent for now

    if (Root == nullptr) { // Special case: we have a brand new empty tree
        Root = N;      // the new vertex is added as the root
    } else { // the tree is not empty
        Vertex *V = Root;       // V will point to the current vertex
        Vertex *Parent = nullptr;  // Parent will always point to V's parent

        // go down the tree until you cannot go any further
        while (V != nullptr) {
            if (N->Elem->Id == V->Elem->Id) { // the element already exists
                cerr << "Elem already exist with Id: " << N->Elem->Id << endl;
                return;
            } else if (*(N->Elem) < *(V->Elem)) { // what I have is smaller than V
                Parent = V;
                V = V->Left;
            } else { // what I have is bigger than V
                Parent = V;
                V = V->Right;
            }
        }

        // reached nullptr -- Must add N as the Parent's child
        if (Parent == nullptr) {
            cerr << "Error: something went wrong parent node is null" << endl;
            return;
        }
        if (*(N->Elem) < *(Parent->Elem)) {
            Parent->Left = N; // N is inserted as the left node of the parent
            N->Up = Parent; // N Up pointer point to it's parent
            // *** EC call here to adjust height and BF
        } else {
            Parent->Right = N; // N is inserted ad the right node of the parent
            N->Up = Parent; // N Up pointer point to it's parent
            // *** EC call here to adjust height and BF
        }
    }
}


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove 
void BST::DeleteVertex(Elem_t *E) {
    Vertex *V = Root;       // the current vertex
    Vertex *Parent = nullptr;  // Parent will always point to V's parent

    // case 1: Lonely Root  --------------------
    if ((*E == *(Root->Elem)) && ((Root->Left == nullptr) && (Root->Right == nullptr))) {
        delete Root; // deleting the Root because there is no other node
        Root = nullptr;
        return;
    }

    // case 2:  One Substree Root ----------------
    // ** if what you want to delete is the root
    if (*(Root->Elem) == *E && ((Root->Left != nullptr) ^ (Root->Right != nullptr))) {
        if (Root->Left != nullptr) { // ** and it has only the left subtree
            Root = Root->Left; // changing the root to the left child
            Root->Up = nullptr;
            delete V; // deleting the old Root
            return;
        } else if (Root->Right != nullptr) { // ** and it has only the right subtree
            Root = Root->Right; // changing the root to the right child
            Root->Up = nullptr;
            delete V; // deleting the old Root
            return;
        }
    }

    // ---- Otherwise deleting something else  --------------

    // going down the tree looking for E
    if (!PreOrderSearch(Root, E, V, nullptr)) {
        cerr << "Did not find the key in the tree." << endl;
        return;
    }
    Parent = V->Up;
    return remove(V, Parent); // removing the element
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P) {
    // ** if V is a leaf (case 1)
    Vertex *C = nullptr;

    if (V->Left == nullptr && V->Right == nullptr) { // Case 1
        if (P->Left == V) // V is the left child of P
            P->Left = nullptr; // remove the deleted element reference from the parent
        else if (P->Right == V) // V is the right child of the Parent
            P->Right = nullptr; // remove the deleted element reference from the parent
        delete V;
    } else if ((V->Left != nullptr) ^ (V->Right != nullptr)) { // Case 2
        if (V->Left != nullptr) { // V has just the left child so bypass V (case 2)
            C = V->Left; // the left child
        } else { // ** if V has just the right child so bypass V (case 2)
            C = V->Right;  // the right child
        }
        C->Up = P;
        if (P->Left == V)
            P->Left = C;
        else
            P->Right = C;
        delete V;
    } else { // V has two children (case 3)
        Elem_t *Melem = nullptr;
        // find MAX element in the left sub-tree of V
        Melem = findMax(V);
        V->Elem = Melem;
    }//end of V with two children
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
Elem_t *BST::findMax(Vertex *V) {
    Vertex *Parent = V;
    printTree(Root, nullptr, false);
    if (V->Left == nullptr && V->Right == nullptr)
        return V->Elem;
    V = V->Left;          // start with the left child of V
    // ** while the right child of V is still available
    while (V->Right != nullptr) {
        Parent = V;
        V = V->Right;
        // ** update Parent and V to go to the right
    }
    // reached nullptr Right  -- V now has the MAX element
    Elem_t *X = V->Elem;
    remove(V, Parent);    // remove the MAX vertex
    return X;             // return the MAX element
}

void BST::setType(Elem_t::ElemType newType, bool reorder) {
    std::vector<Elem_t *> *tmp = nullptr;

    type = newType;
    if (reorder) {
        tmp = new std::vector<Elem_t *>();
        InOrderTraversal(Root, tmp);
        cerr << "Clearing the tree" << endl;
        dTraverse(Root);
        cerr << Root;
        cerr << "Tree cleared" << endl;
        for (Elem_t *elem : *tmp) {
            InsertVertex(elem);
        }
    }
}

Elem_t::ElemType BST::getType() {
    return type;
}

std::vector<Elem_t *> *BST::getOrderdNodes() {
    std::vector<Elem_t *> *tmp = new std::vector<Elem_t *>;
    InOrderTraversal(Root, tmp);
    return tmp;
}
// end of FindMax
