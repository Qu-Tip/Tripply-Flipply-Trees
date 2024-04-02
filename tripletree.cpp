/**
 * @file        tripletree.cpp
 * @description Student-implemented functions of a ternary tree for CPSC 221 PA3.
 *
 *              THIS FILE WILL BE SUBMITTED FOR GRADING
 */

#include "tripletree.h"

 /**
      * Constructor that builds a TripleTree out of the given PNG.
      *
      * The TripleTree represents the subimage from (0,0) to (w-1, h-1) where
      * w-1 and h-1 are the largest valid image coordinates of the original PNG.
      * Every node corresponds to a rectangle of pixels in the original PNG,
      * represented by an (x,y) pair for the upper left corner of the
      * square and two integers for the number of pixels on the width and
      * height dimensions of the rectangular region the node defines.
      *
      * The node's three children correspond to a partition
      * of the node's rectangular region into three approximately equal-size strips.
      *
      * If the rectangular region is taller than it is wide, the region is divided
      * into horizontal strips:
      *  +-------+
      *  |   A   |
      *  |       |
      *  +-------+
      *  |   B   |
      *  |       |    (Split tall)
      *  +-------+
      *  |   C   |
      *  |       |
      *  +-------+
      *
      * If the rectangular region is wider than it is tall, the region is divided
      * into vertical strips:
      *  +---------+---------+---------+
      *  |    A    |    B    |    C    |
      *  |         |         |         |    (Split wide)
      *  +---------+---------+---------+
      *
      * Your regions are not guaranteed to have dimensions exactly divisible by 3.
      * If the dimensions of your rectangular region are 3p x q or q x 3p where 3p
      * represents the length of the long side, then your rectangular regions will
      * each have dimensions p x q (or q x p)
      *
      * If the dimensions are (3p+1) x q, subregion B gets the extra pixel of size
      * while subregions A and C have dimensions p x q.
      *
      * If the dimensions are (3p+2) x q, subregions A and C each get an extra pixel
      * of size, while subregion B has dimensions p x q.
      *
      * If the region to be divided is a square, then apply the Split wide behaviour.
      *
      * Every leaf in the constructed tree corresponds to a pixel in the PNG.
      *
      * @param imIn - the input image used to construct the tree
      */
TripleTree::TripleTree(PNG& imIn) {
    
    unsigned int width = imIn.width();
    unsigned int height = imIn.height();
    pair<unsigned int, unsigned int> ul = make_pair(0, 0);
    root = BuildNode(imIn, ul, width, height);
	
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. It may be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average color stored in the node.
 *
 * You may want a recursive helper function for this.
 */
PNG TripleTree::Render() const {
    // replace the line below with your implementation
    return PNG();
}

/*
 * Prune function trims subtrees as high as possible in the tree.
 * A subtree is pruned (cleared) if all of its leaves are within
 * tol of the average color stored in the root of the subtree.
 * Pruning criteria should be evaluated on the original tree, not
 * on a pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want a recursive helper function for this.
 *
 * @param tol - maximum allowable RGBA color distance to qualify for pruning
 */
void TripleTree::Prune(double tol) {
    // add your implementation below
	
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be mirrored horizontally (flipped over a vertical axis).
 * This may be called on pruned trees and/or previously flipped/rotated trees.
 *
 * You may want a recursive helper function for this.
 */
void TripleTree::FlipHorizontal() {
    // add your implementation below
	
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees counter-clockwise.
 * This may be called on pruned trees and/or previously flipped/rotated trees.
 *
 * You may want a recursive helper function for this.
 */
void TripleTree::RotateCCW() {
    // add your implementation below
	
}

/*
 * Returns the number of leaf nodes in the tree.
 *
 * You may want a recursive helper function for this.
 */
int TripleTree::NumLeaves() const {
    // replace the line below with your implementation
    return countLeaves(root);
}

/**
     * Destroys all dynamically allocated memory associated with the
     * current TripleTree object. To be completed for PA3.
     * You may want a recursive helper function for this one.
     */
void TripleTree::Clear() {

    clearHelper(root);
    
    /*
    for node

    if have children 

    visit children

    if not 

    delete 
    */
	
}

/**
 * Copies the parameter other TripleTree into the current TripleTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other - The TripleTree to be copied.
 */
void TripleTree::Copy(const TripleTree& other) {
    // add your implementation below
    root = copyHelper(other.root); 
	
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param im - reference image used for construction
 * @param ul - upper left point of node to be built's rectangle.
 * @param w - width of node to be built's rectangle.
 * @param h - height of node to be built's rectangle.
 */

Node* TripleTree::BuildNode(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h) {

    // Base Case #1
    if (w == 0 && h == 0) {
        return nullptr;
    } 
    
    Node* n = new Node(ul, w, h);
    pair<unsigned int, unsigned int> A = ul;
    pair<unsigned int, unsigned int> B;
    pair<unsigned int, unsigned int> C;

    // Base case #2 (Leaf Node)
    if (w == 1 && h == 1) { 
        RGBAPixel* pixel = im.getPixel(ul.first, ul.second);
        n->avg = *pixel;                                      
        return n;
    } 
    
    if ((w == 2 && h == 1) || (h == 2 && w == 1)) { //2x1
        
        if (w > h) {
            C = make_pair(ul.first + (w / 2), ul.second);
            n->A = BuildNode(im, A, w/2, h);
            n->C = BuildNode(im, C, w/2, h);
            setColorAvg(n);

        } else {
            C = make_pair(ul.first, ul.second + (h / 2));
            n->A = BuildNode(im, A, w, h/2);
            n->C = BuildNode(im, C, w, h/2);
            setColorAvg(n);
        }

        return n;

    }
    
    if (w == 2 && h == 2) {
        C = make_pair(ul.first + (w / 2), ul.second);
        n->A = BuildNode(im, A, w/2, h);
        n->C = BuildNode(im, C, w/2, h);
        setColorAvg(n);

        return n;

    } 

    if (w >= h) {                // split wide
        if (w % 3 == 1) {       // 3p+1 x q 
            B = make_pair(ul.first + (w / 3), ul.second);       
            C = make_pair(ul.first + (w / 3) + (w / 3) + 1, ul.second);     // + 1 since B gets extra pixel
            n->A = BuildNode(im, A, w/3, h);
            n->B = BuildNode(im, B, w/3 + 1, h);
            n->C = BuildNode(im, C, w/3, h);

        } else if (w % 3 == 2) {      // 3p+2 x q
            B = make_pair(ul.first + (w / 3) + 1, ul.second);               // + 1 since A gets extra pixel
            C = make_pair(ul.first + (w / 3) + (w / 3) + 1, ul.second);     // + 1 since A gets extra pixel
            n->A = BuildNode(im, A, w/3 + 1, h);                            // extra pixel for A
            n->B = BuildNode(im, B, w/3, h);
            n->C = BuildNode(im, C, w/3 + 1, h);                            // extra pixel for C

        } else {        // 3p x q
            B = make_pair(ul.first + (w / 3), ul.second);
            C = make_pair(ul.first + (w / 3) + (w / 3), ul.second);
            n->A = BuildNode(im, A, w/3, h);
            n->B = BuildNode(im, B, w/3, h);
            n->C = BuildNode(im, C, w/3, h);
        }

    } else {                    // split high
        if (h % 3 == 1) {       // p x 3q+1
            B = make_pair(ul.first, ul.second + (h / 3));
            C = make_pair(ul.first, ul.second + (h / 3) + (h / 3) + 1);
            n->A = BuildNode(im, A, w, h/3);
            n->B = BuildNode(im, B, w, h/3 + 1);
            n->C = BuildNode(im, C, w, h/3);

        } else if (h % 3 == 2) {      // p x 3q+2
            B = make_pair(ul.first, ul.second + (h / 3) + 1);
            C = make_pair(ul.first, ul.second + (h / 3) + (h / 3) + 1);
            n->A = BuildNode(im, A, w, h/3 + 1);
            n->B = BuildNode(im, B, w, h/3);
            n->C = BuildNode(im, C, w, h/3 + 1);

        } else {        // p x 3q
            B = make_pair(ul.first, ul.second + (h / 3));
            C = make_pair(ul.first, ul.second + (h / 3) + (h / 3));
            n->A = BuildNode(im, A, w, h/3);
            n->B = BuildNode(im, B, w, h/3);
            n->C = BuildNode(im, C, w, h/3);
        }
    }

    setColorAvg(n);
    return n;

}

/* ===== IF YOU HAVE DEFINED PRIVATE MEMBER FUNCTIONS IN tripletree_private.h, IMPLEMENT THEM HERE ====== */

/*
 * Helper function for BuildNode
 */
void TripleTree::setColorAvg(Node* node) {
    
    if (node->A == nullptr && node->B == nullptr && node->C == nullptr) {
        return;
    }

    int totalPixels = node->width * node->height;
    double redSum = 0, greenSum = 0, blueSum = 0, alphaSum = 0;

    if (node->A != nullptr) {
        setColorAvg(node->A);
        double pixelsA = node->A->width * node->A->height;
        redSum += node->A->avg.r * pixelsA;
        greenSum += node->A->avg.g * pixelsA;
        blueSum += node->A->avg.b * pixelsA;
        alphaSum += node->A->avg.a * pixelsA;
    }

    if (node->B != nullptr) {
        setColorAvg(node->B);
        double pixelsB = node->B->width * node->B->height;
        redSum += node->B->avg.r * pixelsB;
        greenSum += node->B->avg.g * pixelsB;
        blueSum += node->B->avg.b * pixelsB;
        alphaSum += node->B->avg.a * pixelsB;
    }

    if (node->C != nullptr) {
        setColorAvg(node->C);
        double pixelsC = node->C->width * node->C->height;
        redSum += node->C->avg.r * pixelsC;
        greenSum += node->C->avg.g * pixelsC;
        blueSum += node->C->avg.b * pixelsC;
        alphaSum += node->C->avg.a * pixelsC;
    }

    // Calculate the weighted average color
    node->avg = RGBAPixel(redSum/totalPixels, greenSum/totalPixels, blueSum/totalPixels, alphaSum/totalPixels);
} 

/*
 * Helper function for clear
 */
void TripleTree::clearHelper(Node*& node) {

    if (node == nullptr) {
        return;
    }

    clearHelper(node->A);
    clearHelper(node->B);
    clearHelper(node->C);

    delete node;
    node = nullptr;
}

/*
 * Helper function for copy
 */
Node* TripleTree::copyHelper(const Node* source) {
    if (source == nullptr) {
        return nullptr; 
    }

    Node* newNode = new Node(source->upperleft, source->width, source->height);
    newNode->avg = source->avg; 

    newNode->A = copyHelper(source->A);
    newNode->B = copyHelper(source->B);
    newNode->C = copyHelper(source->C);

    return newNode;
}

/*
 * Helper function for numLeaves
 */
int TripleTree::countLeaves(const Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    if (node->A == nullptr && node->B == nullptr && node->C == nullptr) {
        return 1;
    }

    return countLeaves(node->A) + countLeaves(node->B) + countLeaves(node->C);
}
