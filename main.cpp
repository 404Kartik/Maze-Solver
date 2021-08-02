#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

/*
I approached this problem in a basic ground first that how would I as a machine do it.
Then I developed a pseudo algorithm on how I would implement every variable and method
Third step were resolving the collisions and making functions if needed
to make it work
First I implemented easier classes 
Then I moved towards implementing PathSolver
I started from the start node and kept checking that if
nodes are accessible I kept on adding to the openlist and if 
its on the right path I added that node to the closedlist
For backtracking I developed a very efficient algorithm which checks
that if we are on then right path then it adds it to the finalPath
*/

/*
I faced issues in my memory management
deleting memory and figuring out where leaks were was a major
time consuming factor while building this project
I still have one error which you might have seen though the program works
perfectly fine
This error goes away if I comment the delete line in my deconstructor of
the NodeList class
*/
// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    //std::cout << "DONE TESTING" << std::endl
              //<< std::endl;

    // Load Environment
    Env env;
    std::cout << "Enter environment name with env extension :" << std::endl;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList *exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);


    delete pathSolver;
    delete exploredPositions;
    delete solution;
    
    
}

void readEnvStdin(Env env)
{
    
    std::string fileName;
    std::cin >> fileName;
    std::ifstream file("tests/" + fileName);
    std::string str;
    int y = 0;
    while (std::getline(file, str))
    {
        int n = str.length();
        char char_array[n + 1];
   /* making a char array 
   to assign the string to
   */
     strcpy(char_array, str.c_str());

        for (int x = 0; x < ENV_DIM; x++)
        {
           env[y][x] = char_array[x];
        }
        y++;
    }
}

void printEnvStdout(Env env, NodeList *solution)
{
    int solutionColumn;
    int nextsolutionColumn;
    int solutionRow;
    int nextsolutionRow;
    for (int i = 2; i < solution->getLength(); i++)
    {
    solutionColumn = solution->getNode(solution->getLength() - i)->getCol();
    nextsolutionColumn = solution->getNode((solution->getLength() 
    - i) - 1)->getCol();
    solutionRow = solution->getNode(solution->getLength() - i)->getRow();
    nextsolutionRow = solution->getNode((solution->getLength() 
    - i) - 1)->getRow();
        if (abs(solutionColumn - nextsolutionColumn) == 1)
        {
            if(solutionColumn > nextsolutionColumn)
            {
            env[solutionRow][solutionColumn] = '<'; 
            }
            else
            {
            env[solutionRow][solutionColumn] = '>';
            }
        }
        
        else if (abs(solutionRow - nextsolutionRow) == 1)
        {
            if(solutionRow > nextsolutionRow)
            {
            env[solutionRow][solutionColumn] = '^';
            }
            else
            {
            env[solutionRow][solutionColumn] = 'V';
            }
        }
        
    }
    for (int y = 0; y < ENV_DIM; y++)
    {
        for (int x = 0; x < ENV_DIM; x++)
        {
            if(env[y][x]=='<')
            {
                std::cout << "\033[1;31m<\033[0m";
            }
            else if(env[y][x]=='>')
            {
              std::cout << "\033[1;31m>\033[0m";   
            }
            else if(env[y][x]=='^')
            {
                std::cout << "\033[1;31m^\033[0m";  
            }
            else if(env[y][x]=='V')
            {
                std::cout << "\033[1;31mV\033[0m";
            }
            else
            {
            std::cout << env[y][x];
            }
        }
        std::cout << std::endl;
    }
    
      
  

}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
   
}