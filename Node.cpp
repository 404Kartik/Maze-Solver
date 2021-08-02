#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}
Node::Node(Node &other)
{
    this->row = other.row;
    this->col = other.col;
    this->dist_traveled = other.dist_traveled;
}

Node::~Node()
{
    
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    int manhattanDistance = (col - goal->col) + (row - goal->col);
    int estimatedDist = manhattanDistance + dist_traveled;
    return estimatedDist;
}

//--------------------------------