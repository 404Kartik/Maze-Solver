#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    
}

PathSolver::~PathSolver()
{
    //preventing potential memory leaks
     delete nodesExplored;
     delete OpenList;
}

void PathSolver::forwardSearch(Env env)
{
    int goalColumn;
    int goalRow;
    int startColumn;
    int startRow;
    for (int y = 1; y < ENV_DIM - 1; y++)
    {  // start from 1 as the sides are given to be a wall
        for (int x = 1; x < ENV_DIM - 1; x++)
        {
            if (env[y][x] == SYMBOL_START)
            {
                startColumn = x;
                startRow = y;
            }
            else if (env[y][x] == SYMBOL_GOAL)
            {
                goalColumn = x;
                goalRow = y;
            }
        }
    }
    Node *Start = new Node(startRow, startColumn, 0);
    Node *Goal = new Node(goalRow, goalColumn, 0);
     OpenList=new NodeList();
    nodesExplored = new NodeList(); 
    OpenList->addElement(Start); //open list
    Node *currentnode = OpenList->getNode(0);  //current node
    Node *q = OpenList->getNode(0);  
   // int x = startColumn;
    //int y = startRow;

    bool goalFound = false;

    while (goalFound == false)
    {
        currentnode = OpenList->getNode(0); // currentNode as first node
        for (int i = 0; i < OpenList->getLength(); i++)
        {
            if (nodesExplored->contains(OpenList->getNode(i)) == false)
            {
                
                if (currentnode == OpenList->getNode(0))
                {
                    currentnode = OpenList->getNode(i);
                }
                /**
                 * Setting the currentnode to the first node
                 * as it can be the node we travelled to
                */
                if (OpenList->getNode(i)->getEstimatedDist2Goal(Goal) <
                 currentnode->getEstimatedDist2Goal(Goal))
                {
                // finding the node which has the shortest absolute distance
                    currentnode = OpenList->getNode(i);
                }
            }
        }

        // We traverse through every element in the maze
        for (int y = 1; y < ENV_DIM-1; y++)
        {
            for (int x = 1; x < ENV_DIM-1; x++)
            {
                if (goalFound == false)
                {
                    /**
                     *  If we can travel to the next node from where we are, then
                    *  that node will have either a matching 
                    * row or matching column.
                    */
                    if (currentnode->getRow() == y || currentnode->getCol() == x)
                    {
                        /**
                         We test the currentnode if and only if it is in the 
                         range of one step from our current rows 
                         and columns in the maze
                        */
                        if (abs((x + y) - (currentnode->getCol() 
                        + currentnode->getRow())) == 1)
                        {
                            // This element in the node should not be a wall to be tested
                            if (!(env[y][x] == SYMBOL_WALL))
                            {
                                /* We assign the test node to a new value 
                                but distance travelled is one more
                                */
                                q = new Node(y, x, currentnode->
                                getDistanceTraveled() + 1);
                                /*Making sure that if this node has 
                                already been tested or not
                                */
                                if (!OpenList->contains(q))
                                {
                                    if (env[y][x] == SYMBOL_GOAL)
                                    {
                                        goalFound = true;
                                    }
                                    OpenList->addElement(q);
                                }
                                else
                                {
                                // var-q is not needed if its been tested
                                    delete q;
                                }
                            }
                        }
                    }
                }
            }
        }
        nodesExplored->addElement(currentnode);
        // adding the currentnode to the nodes which have been explored
    } 

    nodesExplored->addElement(q);

    delete Goal;
    //deleting the Goal node as we dont need it after this
      
   
}

NodeList *PathSolver::getNodesExplored()
{
    // making a deep copy before returning
    NodeList *nodelist = new NodeList(*nodesExplored);
    return nodelist;
}

NodeList *PathSolver::getPath(Env env)
{
    NodeList *finalPath = new NodeList();
    bool reachedStart = false;
    int testedColumn;
    int testedRow;
    int finalColumn;
    int pathRow;
finalPath->addElement(nodesExplored->getNode(nodesExplored->getLength() - 1));
    while (reachedStart == false)
    {
        for (int i = 0; i < nodesExplored->getLength(); i++)
        {
            if (reachedStart == false)
            {
              testedColumn = nodesExplored->getNode(i)->getCol();
              testedRow = nodesExplored->getNode(i)->getRow();
              finalColumn = finalPath->getNode(finalPath->getLength() 
              - 1)->getCol();
              pathRow = finalPath->getNode(finalPath->getLength() 
              - 1)->getRow();

                
                 /* If the next node is accessible then 
                 it atleast have one dimension in common
                */
                if (testedRow == pathRow || testedColumn == finalColumn)
                {
                   if (abs((finalColumn + pathRow) - 
                   (testedColumn + testedRow)) == 1)
                    {
                        /*Checking if the node is an adjacent 
                        node of the current node
                        */
                        if (finalPath->getNode(finalPath->getLength() 
                        - 1)->getDistanceTraveled() -
                        nodesExplored->getNode(i)->getDistanceTraveled() == 1)
                        {
                            finalPath->addElement(nodesExplored->getNode(i));
                            if (env[nodesExplored->getNode(i)->getRow()]
                            [nodesExplored->getNode(i)->getCol()] 
                            == SYMBOL_START)
                            {
                                reachedStart = true;
                            }
                        }
                    }
                }
            }
        }
    }
    //creating a deepcopy of the finalPath nodelist
    NodeList *copyFinalPath = new NodeList(*finalPath);
    delete finalPath;
    return copyFinalPath;
}
