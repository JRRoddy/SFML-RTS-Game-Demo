#include "QuadTree.h"


// a quad tree data structure is a spatial partitioning structure that is desgined to reduce the weight of collision checks 
/// the idea is to continously divide a space into smaller and smaller quads where each quad 
//  has a bucket of game objects who's bounds were able to fit into the quad, this divides 
// the space up meaning that each game object has its own section allocated to it 
// this reduces the amount of checks required when it comes to collision detection 
// as the quad tree can be queried based on an objects bounds i.e the range that object covers 
// and only the spaces within the quad tree data structure covered by the objects bounds need to be checked 

// the quad tree follows a recursive desgin patter with a root node that links all of the subsections/branches of the tree  togther























