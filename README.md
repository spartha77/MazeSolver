# MazeSolver
2D Maze solver

Preamble: The repository contains two different components, 1. The architecture that enables creation of commands and 1. The functionality that runs when invoking the command
It is implemented in VS2019, with C++20. It is not developed for any other platform

Overview: This project solves a maze (2D) if the initial position is given as input. The maze in 2D is provided as a matrix (please refer to maze_1.txt). A vertex graph is contructed with the input. Two strategies are used to find the path, a. Depth First Search : This gives all possible paths (from root to the last possible leaf node (or the one that is connected again to already visited node) and the solution path(s), if this finds a solution to the maze b. Another strategy called as A* algorithm. <b>(Please note that for the sake of simplicity, I have manually fed the input and outputs)</b>

The idea behind the two strategies are 1. DFS simulates the initial unknown nature of the maze. ALl possible paths are explored. This gives out all possible solutions, with start and end locations.
Subsequyently, A* algorithm optimizes the solutions thus found to have the shortest path with the heuristics set to guide the algorithm as to how far the target is from any location. The respective measures from source and target distance (with edge weight as 1) is set using Breadth First Search transits. 

THe mazesolver.cpp acts as the client. 

Salient features of the design:
a. The maze is modeled as a graph. So, a path can be explored from any starting location, in the matrix. '1' denotes path way, while '0' denotes blocked way.
b. The functionalities such as CReation of Graph, Path finding are implemented as close to stateless commands. THese commands can be interfaced with any other scripting language too.

The maze solver client contains the sample code to run and test. 

The current matrix look as 
10
10
0 0 0 0 1 0 0 0 0 0   
0 1 1 1 1 1 1 1 1 0  
0 1 0 0 0 1 0 0 1 0   
0 0 0 1 1 1 1 0 1 0   
0 1 1 1 0 0 0 0 1 0   
0 0 0 1 1 1 0 1 1 0  
0 1 0 0 0 1 0 0 0 0   
0 1 1 1 1 1 0 0 1 0   
0 0 1 0 0 1 1 1 1 0   
0 0 0 0 0 0 0 1 0 0  
  
The above matrix has 1s where the given problem has white cell and 0 where there is a black cell. THe output from the solver (in the IO stream) is the index of the matrix with index starting from 0 for rows and columns. This matrix can be changed to any input problem.
  
The design:  
The solution caontains the following patterns  
1. Command ( to run a pre-defined chunk of steps to achieve a specific functionality). The commands are created by CommandsFactory ( Factory pattern) with a singleton pattern. The commands ideally are templated interfaces (input/output types) and are stored in the multiType container. Each command for a particular input and output type is singleton and are queeried by "String" that the commands are referred to.  
2. Each instance of Factory and commands Manager are singleton.  
3. The actual running of the commands' execution are honoured by commands executors. The commands pattern and the executors are highly loosely coupled so that they can vary independently. Example ICommand is implemented by GenericCommand, which is then implemented by GenericCommandImplWrapper, but the executor is set to the Impl wrapper. The design is type safe (static time).  

The functionality:  
1. Depth First Search is implemented by using stack and path (vector).  
2. The Graph is a templated class of GraphNode<Node>. A graph node is a data structure that is used to connect to another graph node, which has flags, children (siblings) etc., The Node is a end user data type which is not used for modification but used only for association. IN this way, I do not pollute the user provided Nodes, that actually form the network. The graphnode is the one that has all mechanism to connect but keeps the Node away.  
  
Usage:  
  1. Modify the matrix defined in the file maze_1.txt. This is hard coded as the command line argumemnts. Please change the path to the file accordingly.  
  2. Load the MazeSolver.sln in VS2019 and build, with x64 config.  
  3. Run the executable.  
    
 Results:  
    
  CommandsManager's instance created  
Command : GraphCreationCommand created!  
Command : GraphPathFinderCommand created!  
0       0       0       0       1       0       0       0       0       0  
0       1       1       1       1       1       1       1       1       0  
0       1       0       0       0       1       0       0       1       0  
0       0       0       1       1       1       1       0       1       0  
0       1       1       1       0       0       0       0       1       0  
0       0       0       1       1       1       0       1       1       0  
0       1       0       0       0       1       0       0       0       0  
0       1       1       1       1       1       0       0       1       0  
0       0       1       0       0       1       1       1       1       0  
0       0       0       0       0       0       0       1       0       0  
  
Graph Creation command Executed  
ASTAR algorithm in progress  
node    0,4     m_FF    0       m_HH    16      m_EVAL  16  
node    1,4     m_FF    1       m_HH    15      m_EVAL  16  
node    1,5     m_FF    2       m_HH    14      m_EVAL  16  
node    2,5     m_FF    3       m_HH    13      m_EVAL  16  
node    3,5     m_FF    4       m_HH    12      m_EVAL  16  
node    3,4     m_FF    5       m_HH    11      m_EVAL  16  
node    3,3     m_FF    6       m_HH    10      m_EVAL  16  
node    4,3     m_FF    7       m_HH    9       m_EVAL  16  
node    5,3     m_FF    8       m_HH    8       m_EVAL  16  
node    5,4     m_FF    9       m_HH    7       m_EVAL  16  
node    5,5     m_FF    10      m_HH    6       m_EVAL  16  
node    6,5     m_FF    11      m_HH    5       m_EVAL  16  
node    7,5     m_FF    12      m_HH    4       m_EVAL  16  
node    8,5     m_FF    13      m_HH    3       m_EVAL  16  
node    8,6     m_FF    14      m_HH    2       m_EVAL  16  
node    8,7     m_FF    15      m_HH    1       m_EVAL  16  
node    9,7     m_FF    16      m_HH    0       m_EVAL  16  
ASTAR algorithm in ENDED  
  
Graph Path Finder command Executed  

 Feasible solution Paths in DFS strategy are  

Path - 1  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        8,5  
        8,6  
        8,7  
        9,7  
DFS maze solver algorithm in progress  
  
Graph Path Finder command Executed  

 All Possible Paths in DFS strategy are  

Path - 1  
        0,4  
        1,4  
        1,3  
        1,2  
        1,1  
        2,1  
  
Path - 2  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        8,5  
        8,6  
        8,7  
        9,7  
  
Path - 3  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        8,5  
        8,6  
        8,7  
        8,8  
        7,8  
  
Path - 4  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        7,4  
        7,3  
        7,2  
        8,2  
  
Path - 5  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        7,4  
        7,3  
        7,2  
        7,1  
        6,1  
  
Path - 6  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        4,2  
        4,1  
  
Path - 7  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,6  
  
Path - 8  
        0,4  
        1,4  
        1,5  
        1,6  
        1,7  
        1,8  
        2,8  
        3,8  
        4,8  
        5,8  
        5,7  
  
 Feasible solution Paths in DFS strategy are  

Path - 1  
        0,4  
        1,4  
        1,5  
        2,5  
        3,5  
        3,4  
        3,3  
        4,3  
        5,3  
        5,4  
        5,5  
        6,5  
        7,5  
        8,5  
        8,6  
        8,7  
        9,7  
  
  
    
  Feasible solution Path is the solution. The results can be more than 1 but the given problem has only one solution. Either starting from 0,4 or 9,7  
  
  
  
