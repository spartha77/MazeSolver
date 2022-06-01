#pragma once
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <algorithm>
#include <functional>

#include "MyPriorityQueue.h"
#include "GraphNode.h"





template <typename GraphNodeType, typename NodeType>
class Graph
{
private:

    std::vector<std::unique_ptr<GraphNodeType>> m_GraphNodes;
    std::vector<std::unique_ptr<NodeType>> m_Nodes;

    int** m_MazeMatrix = nullptr;
    int m_Rows = -1, m_Cols = -1;

    std::vector< std::vector< GraphNodeType*>> m_AllDFSPaths;
    std::vector< std::vector< GraphNodeType*>> m_AllSolutionPaths;

    

    void createNodes(const int& val, const int& row, const int& col)
    {
        auto iter = std::find_if(m_GraphNodes.begin(), m_GraphNodes.end(), [val, row, col, this](std::unique_ptr<GraphNodeType>& gnd)
            {
                return (*(gnd.get()) == GraphNodeType{ gnd->getNode(), row, col, this->m_Rows, this->m_Cols});
            });
        if (iter == m_GraphNodes.end())
        {
            m_Nodes.emplace_back(std::make_unique<NodeType>(val));
            m_GraphNodes.emplace_back(std::make_unique<GraphNodeType>(m_Nodes[m_Nodes.size() - 1].get(), row, col, m_Rows, m_Cols));
        }
    }
public:
    Graph() {}
    Graph(Graph&& rhs):
        m_GraphNodes(std::move(rhs.m_GraphNodes)),
        m_Nodes(std::move(rhs.m_Nodes)),
        m_AllDFSPaths(std::move(rhs.m_AllDFSPaths)),
        m_AllSolutionPaths(std::move(rhs.m_AllSolutionPaths)),
        m_Rows(std::move(rhs.m_Rows)),
        m_Cols(std::move(rhs.m_Cols))
    {
        m_MazeMatrix = rhs.m_MazeMatrix;
        rhs.m_MazeMatrix = nullptr;
    }
    void printPaths(std::vector<std::vector<GraphNode<Node>*>>& paths)
    {
        int count = 1;
        std::for_each(paths.begin(), paths.end(), [&count](std::vector<GraphNode<Node>*> nodeVec)
            {
                std::cout << "\nPath - " << count++ << "\n";
                std::for_each(nodeVec.begin(), nodeVec.end(), [](GraphNode<Node>* item)
                    {
                        std::cout << "\t" << item->getRow() << "," << item->getCol() << std::endl;
                    });
            });
    }
    ~Graph()
    {
        for (int ii = 0; ii < m_Rows; ii++)
        {
            delete[] m_MazeMatrix[ii];
        }
        delete [] m_MazeMatrix;
    }
    int GetTotalRows()
    {
        return m_Rows;
    }
    int GetTotalColumns()
    {
        return m_Rows;
    }
    std::vector<GraphNodeType*> GetEndNodes()
    {
        std::vector<GraphNodeType*> result;
        std::for_each(m_GraphNodes.begin(), m_GraphNodes.end(), [&result, this](std::unique_ptr<GraphNodeType>& gnd)
            {
                if (gnd->getRow() == this->GetTotalRows() - 1 || gnd->getRow() == 0 ||
                    gnd->getCol() == this->GetTotalColumns() - 1 || gnd->getCol() == 0)
                    result.push_back(gnd.get());
            });
        return result;
    }
    GraphNodeType* getGraphNode(const int& row, const int& col)
    {
        GraphNodeType* res = nullptr;
        auto iter = std::find_if(m_GraphNodes.begin(), m_GraphNodes.end(), [row, col, this](std::unique_ptr<GraphNodeType>& gnd)
            {
                NodeType nd;// { val };
                return (*(gnd.get()) == GraphNodeType{ &nd, row, col, this->m_Rows , this->m_Cols });
            });
        if (iter != m_GraphNodes.end())
            res = (*iter).get();

        return res;
    }

    GraphNodeType* getGraphNode(GraphNodeType* rhs)
    {
        GraphNodeType* res = nullptr;
        auto iter = std::find_if(m_GraphNodes.begin(), m_GraphNodes.end(), [rhs, this](std::unique_ptr<GraphNodeType>& gnd)
            {
                NodeType nd;// { val };
                return (*(gnd.get()) == *rhs);
            });
        if (iter != m_GraphNodes.end())
            res = (*iter).get();

        return res;
    }
    void resetFlag()
    {
        for (auto &node : m_GraphNodes)
        {
            node.get()->resetFlag();
        }
    }
    void buildGraph()
    {
        createElements();
        buildLinks();
    }
    void BFS( GraphNodeType* startGraphNode, std::optional<std::function<void(GraphNodeType*)>> visitor_fn_opt)
    {
        resetFlag();
        startGraphNode->BFS(visitor_fn_opt);
        resetFlag();
    }
    std::vector< std::vector< GraphNodeType*>> DFS(GraphNodeType* startGraphNode, 
        std::optional<std::function<void(GraphNodeType*)>> visitor_fn_opt)
    {
        resetFlag();
        std::vector< std::vector< GraphNodeType*>> res;
        if (startGraphNode)
        {
            res = startGraphNode->DFS(visitor_fn_opt);
            resetFlag();
        }
        
        //printPaths(res);
        m_AllDFSPaths = res;
        return res;
    }
    std::vector< std::vector< GraphNodeType*>> getAllSolutionPaths(std::vector< std::vector< GraphNodeType*>>& allPaths)
    {
        std::vector< std::vector< GraphNodeType*>> allSolutionPaths;
        for (auto eachPath : allPaths)
        {
            std::vector<GraphNodeType*> solutionPath;
            if (eachPath.back()->getRow() == m_Rows - 1 || eachPath.back()->getCol() == m_Cols - 1 ||
                eachPath.back()->getRow() == 0 || eachPath.back()->getCol() == 0 )
            {
                std::for_each(eachPath.begin(), eachPath.end(), [&solutionPath](GraphNodeType* graphNodeItem)
                    {
                        solutionPath.push_back(graphNodeItem);
                    });
            }
            if (solutionPath.size() > 0)
                allSolutionPaths.push_back(solutionPath);
        }

        m_AllSolutionPaths = allSolutionPaths;

        return allSolutionPaths;
    }
    void createElements()
    {
        for (int ii = 0; ii < m_Rows; ii++)
        {
            for (int jj = 0; jj < m_Cols; jj++)
            {
                int val = 1;
                if (m_MazeMatrix[ii][jj] == 1)
                {
                    createNodes(val, ii, jj);
                }
            }
        }
    }
    
    std::vector<GraphNodeType*> findPathUsingNonGreedyASTAR(GraphNodeType *startNode, GraphNodeType *endNode)
    {
        std::vector<GraphNodeType*> path;

        if (!startNode || !endNode)
            return path;
        
        startNode->SetPreviousNode(nullptr);
        this->setHeuristicValues(endNode);

        startNode->setMeasureFromSource(0);
        startNode->ComputeEvaluatedValue();

        auto minCmp = [](GraphNodeType* left, GraphNodeType* right) { return left->getEvaluatedValue() > right->getEvaluatedValue(); };
        MyPriorityQueue<GraphNodeType> openMinHeap(minCmp);
        openMinHeap.Push(startNode);

        MyPriorityQueue<GraphNodeType> closedMinHeap(minCmp);

        std::cout << "ASTAR algorithm in progress\n";
        while (!openMinHeap.IsEmpty())
        {
            // Extract the node from openMin Heap
            GraphNodeType* extractedNode = openMinHeap.Extract();
            
            // Assign m_FF to the neighbours of the extracted node and the previous node.
            // This might re-define the m_FF and the previous node
            extractedNode->setMeasureFromSource2Neighbors();

            std::cout << "node\t" << extractedNode->getRow() << "," << extractedNode->getCol() << "\tm_FF\t"
                << extractedNode->getFF().value() << "\tm_HH\t" << extractedNode->getHH().value() 
                << "\tm_EVAL\t"<< extractedNode->getEvaluatedValue().value()<<std::endl;

            // Lambda function to check if the graphNode does not exist (already) in the closedMinHeap
            auto notExistsInClosedPQ = [&closedMinHeap](GraphNodeType* graphNode)
            {
                if (!closedMinHeap.Contains(graphNode))
                    return true;
                return false;
            };
            

            // Add the node in the closed Min Heap
            closedMinHeap.Push(extractedNode);


            if (*extractedNode == *endNode)
            {
                openMinHeap.Clear();
                break;;
            }
            // Get the children of the extracted node
            auto children = extractedNode->GetChildren();

            // Add the children into the openMinHeap ONLY IF the element
            // is not in closedMinHeap
            openMinHeap.Push(children, notExistsInClosedPQ);
        }

        path = closedMinHeap.GetElements();
        std::cout << "ASTAR algorithm in ENDED\n";
        return path;
    }
    void buildLinks()
    {
        int val = 1;
        for (int ii = 0; ii < m_Rows; ii++)
        {
            for (int jj = 0; jj < m_Cols; jj++)
            {
                auto* currNode = getGraphNode(ii, jj);
                if ( currNode )
                {
                    auto northSideGraphNode = getGraphNode(ii - 1, jj);
                    if (northSideGraphNode)
                        currNode->add2Siblings(northSideGraphNode);

                    auto southSideGraphNode = getGraphNode(ii + 1, jj);
                    if (southSideGraphNode)
                        currNode->add2Siblings(southSideGraphNode);

                    auto eastSideGraphNode = getGraphNode(ii, jj-1);
                    if (eastSideGraphNode)
                        currNode->add2Siblings(eastSideGraphNode);

                    auto westSideGraphNode = getGraphNode(ii, jj + 1);
                    if (westSideGraphNode)
                        currNode->add2Siblings(westSideGraphNode);
                }
            }
        }
    }

    void printGraph()
    {
        int val = 1;
        for (int ii = 0; ii < m_Rows; ii++)
        {
            for (int jj = 0; jj < m_Cols; jj++)
            {
                auto* currNode = getGraphNode(ii, jj);
                if (currNode)
                {
                    currNode->print();
                }
            }
        }
    }
    
    void setHeuristicValues(GraphNodeType* targetNode)
    {   
        targetNode->setHH(0);
        auto bfsVisitor = [](GraphNodeType* parentGNode)
        {
            parentGNode->setHeuristicValues2Siblings(parentGNode->getHH().value()+1);
        };
        this->BFS(targetNode, bfsVisitor);
    }

    void setMeasureFromSourceValues(GraphNodeType* startNode)
    {
        startNode->setFF(0);
        auto bfsVisitor = [](GraphNodeType* parentGNode)
        {
            parentGNode->setMeasureFromSource2Siblings(parentGNode->getFF().value() + 1);
        };
        this->BFS(startNode, bfsVisitor);
    }



    void readMazeMatrix(std::string inputFileFilename)
    {
        
        std::ifstream graphMatrixInputFile;
        
        try
        {
            graphMatrixInputFile.open(inputFileFilename.c_str());
            graphMatrixInputFile >> m_Rows >> m_Cols;
            m_MazeMatrix = new int* [m_Rows];
            for (int ii = 0; ii < m_Rows; ii++)
            {
                m_MazeMatrix[ii] = new int[m_Cols];
            }

            {
                int ii = 0;
                int jj = 0;
                while (graphMatrixInputFile >> m_MazeMatrix[ii][jj])
                {
                    jj++;

                    if (jj == m_Cols)
                    {
                        jj = 0;
                        ii++;

                        if (ii == m_Cols)
                            ii = 0;
                    }
                }
            }

        }
        catch (...)
        {
            std::cerr << "Error while reading input file" << std::endl;
            graphMatrixInputFile.close();
        }

        for (int ii = 0; ii < m_Rows; ii++)
        {
            for (int jj = 0; jj < m_Cols; jj++)
            {
                std::cout << m_MazeMatrix[ii][jj] << "\t";
            }
            std::cout << std::endl;
        }

        graphMatrixInputFile.close();
    }
    
    void ReadGraphFromFile(std::string inputFile)
    {
        readMazeMatrix(inputFile);
        buildGraph();
    }
};
