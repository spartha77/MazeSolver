// MazeSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>

#include "Node.h"
#include "Graph.h"
#include "CommandsManager.h"

#include "MyPriorityQueue.h"
#include "InputOutput.h"
#include "Init.h"

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while (!q.empty()) {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}


int main( int argc, char **argv)
{
    
    if (argc != 2)
    {
    
        std::cerr << "Wrong usage or graph definition matrix file not found...\n";
        exit(1);
    }


    Init();

    // First command to create the Graph from maze matrix
    GraphCreationCommandInput graphCreationInputdata{ argv[1] };
    auto creationCommand = CommandsManager::GetInstance()->GetCommand("GraphCreationCommand");
    creationCommand->SetData(std::any(graphCreationInputdata));
    
    // Execute the command GraphCreationCommand
    creationCommand->Execute();

    // Get the data from the GraphCreationCommand command
    GraphCreationCommandOutput output;
    output.m_Graph = nullptr;
    auto anyOutputFromCreateGraphCmd = std::any(output);
    creationCommand->GetData(anyOutputFromCreateGraphCmd);
    auto outputFromCreateGraphCmd = std::any_cast<GraphCreationCommandOutput>(anyOutputFromCreateGraphCmd);
    

    // Path finding using command GraphPathFinderCommand with NonGreedyASTAR strategy
    GraphPathFinderInput graphPathFinderInput;
    graphPathFinderInput.m_StartNode = outputFromCreateGraphCmd.m_EndNodes[0];
    graphPathFinderInput.m_EndNode = outputFromCreateGraphCmd.m_EndNodes[1];
    graphPathFinderInput.m_Strategy = PathFindingSTrategy::NonGreedyASTAR;

    auto graphPathFinderCommandASTARStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
    graphPathFinderCommandASTARStrategy->SetData(std::any(graphPathFinderInput));

    // Set Input to the command GraphPathFinderCommand with NonGreedyASTAR strategy
    graphPathFinderCommandASTARStrategy->Execute();

    // Fetch the output from the command GraphPathFinderCommand with NonGreedyASTAR strategy
    GraphPathFinderOutput pathFinderCmdOutput;
    auto anyPathFinderCmdOutput = std::any(pathFinderCmdOutput);
    graphPathFinderCommandASTARStrategy->GetData(anyPathFinderCmdOutput);
    pathFinderCmdOutput = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdOutput);

    // Print the ASTAR Path
    std::cout << "\n Feasible solution Paths in DFS strategy are" << std::endl;
    outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutput.m_AllSolutionPaths);

    // Path finding using command GraphPathFinderCommand with DFS (Depth First Search) strategy
    graphPathFinderInput.m_StartNode = outputFromCreateGraphCmd.m_EndNodes[0];
    graphPathFinderInput.m_Strategy = PathFindingSTrategy::DFS;


    auto graphPathFinderCommandDFSStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
    // Set Input to the command GraphPathFinderCommand with DFS strategy
    graphPathFinderCommandDFSStrategy->SetData(std::any(graphPathFinderInput));
    
    // Execute the command GraphPathFinderCommand with DFS strategy
    graphPathFinderCommandDFSStrategy->Execute();
    
    // Fetch the output from the command GraphPathFinderCommand with DFS strategy
    anyPathFinderCmdOutput = std::any(pathFinderCmdOutput);
    graphPathFinderCommandDFSStrategy->GetData(anyPathFinderCmdOutput);
    pathFinderCmdOutput = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdOutput);

    std::cout << "\n All Possible Paths in DFS strategy are" << std::endl;
    outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutput.m_AllPaths);

    std::cout << "\n Feasible solution Paths in DFS strategy are" << std::endl;
    outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutput.m_AllSolutionPaths);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
