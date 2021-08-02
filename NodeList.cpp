#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    
}

NodeList::~NodeList()
{
  for(int i=0; i<this->getLength(); i++)
  {
      delete this->getNode(i);
  }
}


NodeList::NodeList(NodeList &other)
{
    for (int i = 0; i < other.length; i++)
    {
        Node *node = new Node(*other.getNode(i));
        this->addElement(node);
    }
    this->length = other.length;
}

int NodeList::getLength()
{
    return this->length;
}

void NodeList::addElement(Node *newPos)
{
    
    nodes[length] = newPos;
    length = length + 1;
}

Node *NodeList::getNode(int i)
{
    return nodes[i];
}

bool NodeList::contains(Node *node)
{
    bool contains = false;
    for (int i = 0; i < this->length; i++)
    {
        if (node->getCol() == nodes[i]->getCol() && 
        node->getRow() == nodes[i]->getRow())
        {
            contains = true;
        }
    }
    return contains;
}