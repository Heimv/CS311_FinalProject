// CS311: BST header file for HW4 - by Yoshii - DO NOT CHANGE!!
// This BST has an Up link to make it easy to go up the tree later 
//------------------------------------------------------------

#pragma once

#include <vector>
#include "../Elem/elem.h"

// definition of what a Vertex is - also hidden from the client
struct Vertex {
    Vertex *Up;  // points to the parent node
    Vertex *Left;
    Elem_t *Elem;
    Vertex *Right;
    int Height;  // for EC
    int Balance;  // for EC
};

// this is set up to be inherited by another class
class BST {

public:
    enum DisplayType {
        INORDER,
        GRAPHICAL
    };
    BST();  // intializes Root
    ~BST();  // destructor calls dtraverse to destroy the dynamic tree

    // PURPOSE: these will show the vertices in IN order
    // TO CALL: No parameter  but provide a pointer to
    //          the root vertex in calling INorderTraversal
    void Display(DisplayType type = GRAPHICAL);

    static void InOrderTraversal(Vertex *, std::vector<Elem_t*>*); // recursive

    // PURPOSE: these will search in PRE order - same as Depth First
    // TO CALL: provide the element to search for; provide a pointer to
    //          the root vertex in calling PREorderSearch
    Elem_t *Search(Elem_t *);
    std::vector<Elem_t*> *Search(int);
    std::vector<Elem_t*> *Search(Elem_t::importance);
    std::vector<Elem_t*> *Search(std::string);
    std::vector<Elem_t*> *Search(bool);

    static bool PreOrderSearch(Vertex *, Elem_t *, Vertex *, std::vector<Elem_t*> *);

    // PURPOSE: This adds a new vertex into the BST
    // TO CALL: provide the element to be added to the tree
    void InsertVertex(Elem_t *);

    // PURPOSE: This deletes a vertex with the given element
    //     - calls remove and  findMax (see below)
    // TO CALL: provide the element to be removed from the tree
    void DeleteVertex(Elem_t *);

    // the following can be inherited but not available to the client
    void setType(Elem_t::ElemType, bool);

    Elem_t::ElemType getType();

    std::vector<Elem_t*> *getOrderdNodes();
protected:
    Elem_t::ElemType type = Elem_t::TITLE;
    struct Trunk
    {
        Trunk *prev;
        std::string str;

        Trunk(Trunk *prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };

    Vertex *Root; //  Root which is a pointer to the root vertex

    // utility functions follow - these are not for the clients to use
    // These were created to implement the public methods

    void dTraverse(Vertex *);
    // traverse and delete all vertices in post order

    void remove(Vertex *, Vertex *);
    // removes the vertex knowing its parent

    Elem_t *findMax(Vertex *);  // finds the MAX element in the
    // left sub-tree of the vertex and also deletes it

    // I found these function to pretty print a binary tree here:
    // https://www.techiedelight.com/c-program-print-binary-tree/
    static void printTree(Vertex *root, Trunk *prev, bool isLeft);
    static void showTrunks(Trunk *p);
};


