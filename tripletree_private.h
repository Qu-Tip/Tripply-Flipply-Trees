/**
 * @file        tripletree_private.h
 * @description student declarations of private functions
 *              for TripleTree, CPSC 221 PA3
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below
void setColorAvg(Node* n);

void clearHelper(Node*& node);

Node* copyHelper(const Node* source);

int countLeaves(const Node* node) const;

void RenderHelper(Node* n, PNG& canvas) const;