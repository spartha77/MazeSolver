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

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Wrong usage or graph definition matrix file not found...\n";
		exit(1);
	}

	// Initialize commands
	Init();

	// Maze to Graph creation command execution
	GraphCreationCommandOutput outputFromCreateGraphCmd;
	{
		// First command to create the Graph from maze matrix. The graph is a singleton object.
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
		outputFromCreateGraphCmd = std::any_cast<GraphCreationCommandOutput>(anyOutputFromCreateGraphCmd);
	}

	// Path finding using command GraphPathFinderCommand with DFS strategy
	GraphPathFinderOutput pathFinderCmdOutputDFSStrategy;
	{
		GraphPathFinderInput graphPathFinderInput;

		// To give two different inputs for the maze_02_2_connected_components.txt, 
		// use outputFromCreateGraphCmd.m_EndNodes[0] OR outputFromCreateGraphCmd.m_EndNodes[1] below.
		// This chooses 0,2 or 0,5
		graphPathFinderInput.m_StartNode = outputFromCreateGraphCmd.m_EndNodes[1];
		graphPathFinderInput.m_Strategy = PathFindingSTrategy::DFS;

		auto graphPathFinderCommandDFSStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
		graphPathFinderCommandDFSStrategy->SetData(std::any(graphPathFinderInput));

		// Set Input to the command GraphPathFinderCommand with NonGreedyASTAR strategy
		graphPathFinderCommandDFSStrategy->Execute();

		// Fetch the output from the command GraphPathFinderCommand with NonGreedyASTAR strategy
		auto anyPathFinderCmdOutputDFSStrategy = std::any(pathFinderCmdOutputDFSStrategy);
		graphPathFinderCommandDFSStrategy->GetData(anyPathFinderCmdOutputDFSStrategy);
		pathFinderCmdOutputDFSStrategy = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdOutputDFSStrategy);

		// Print the DFS paths
		std::cout << "\n All Possible Paths in DFS strategy are" << std::endl;
		outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutputDFSStrategy.m_AllPaths);

		std::cout << "\n Feasible solution Paths in DFS strategy are" << std::endl;
		outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths);

		if (pathFinderCmdOutputDFSStrategy.m_containsCycles)
		{
			std::cout << "\n **The Graph contains one or more cycles **" << std::endl;
		}
	}

	// Path finding by Non Greedy ASTAR algoriothm
	GraphPathFinderInput graphPathFinderASTARStrategyInput;
	GraphPathFinderOutput pathFinderCmdNonGreedyASTAROutput;

	size_t pathIndex = pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths.size() - 1;

	graphPathFinderASTARStrategyInput.m_StartNode = pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths[0][0];
	graphPathFinderASTARStrategyInput.m_EndNode = pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths[pathIndex][pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths[pathIndex].size() - 1];
	graphPathFinderASTARStrategyInput.m_Strategy = PathFindingSTrategy::NonGreedyASTAR;


	auto graphPathFinderCommandDFSStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
	// Set Input to the command GraphPathFinderCommand with DFS strategy
	graphPathFinderCommandDFSStrategy->SetData(std::any(graphPathFinderASTARStrategyInput));

	// Execute the command GraphPathFinderCommand with DFS strategy
	graphPathFinderCommandDFSStrategy->Execute();

	// Fetch the output from the command GraphPathFinderCommand with DFS strategy
	auto anyPathFinderCmdNonGreedyASTAROutput = std::any(pathFinderCmdNonGreedyASTAROutput);
	graphPathFinderCommandDFSStrategy->GetData(anyPathFinderCmdNonGreedyASTAROutput);
	pathFinderCmdNonGreedyASTAROutput = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdNonGreedyASTAROutput);

	std::cout << "\n Feasible solution Path in ASTAR strategy is" << std::endl;
	outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdNonGreedyASTAROutput.m_AllSolutionPaths);

	if (pathFinderCmdNonGreedyASTAROutput.m_containsCycles)
		std::cout << "\n **The Graph contains one or more cycles **" << std::endl;
}