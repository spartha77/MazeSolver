# MazeSolver
2D Maze solver

Preamble: The repository contains two different components, 1. The architecture that enables creation of commands and 1. The functionality that runs when invoking the command
It is implemented in VS2019, with C++20. It is not developed for any other platform

Overview: This project solves a maze (2D) if the initial position is given as input. The maze in 2D is provided as a matrix (please refer to maze_1.txt). A vertex graph is contructed with the input. Two strategies are used to find the path, a. Depth First Search : This gives all possible paths (from root to the last possible leaf node (or the one that is connected again to already visited node) and the solution path(s), if this finds a solution to the maze b. Another strategy called as A* algorithm. <b>(Please note that for the sake of simplicity, I have manually fed the input and outputs)</b>

The idea behind the two strategies are 1. DFS simulates the initial unknown nature of the maze. ALl possible paths are explored. This gives out all possible solutions, with start and end locations.
Subsequyently, A* algorithm optimizes the solutions thus found to have the shortest path with the heuristics set to guide the algorithm as to how far the target is from any location. The respective measures from source and target distance (with edge weight as 1) is set using Breadth First Search transits. 

THe mazesolver.cpp acts as the client. 

<b> Please refer to the files README.txt and Mazes.xlsx for details on how to run the test cases. 4 test cases have been provided.</b>

Please also note that the DFS and non-greedy A* algorithms do not display paths, that forms part of the cycle with the main paths. Nevertheless, both the algorithms detect if there are cycles.

Salient features of the design:
a. The maze is modeled as a graph. So, a path can be explored from any starting location, in the matrix. '1' denotes path way, while '0' denotes blocked way.
b. The functionalities such as CReation of Graph, Path finding are implemented as close to stateless commands. THese commands can be interfaced with any other scripting language too.

The maze solver client contains the sample code to run and test. 
<pre>
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
    
 Results for maze_04_loop_equal_weights_ASTAR.txt
    
CommandsManager's instance created
Command : GraphCreationCommand created!
Command : GraphPathFinderCommand created!
0       0       0       0       1       0       0       0       0       0
0       0       1       1       1       1       1       0       0       0
0       0       1       0       0       0       1       0       0       0
0       0       1       0       0       0       1       0       0       0
0       0       1       0       0       0       1       0       0       0
0       0       1       0       0       0       1       0       0       0
0       0       1       1       1       1       1       0       0       0
0       0       0       0       1       0       0       0       0       0
0       0       0       0       1       0       0       0       0       0
0       0       0       0       1       0       0       0       0       0

Graph Creation command Executed
DFS maze solver algorithm in progress

Graph Path Finder command Executed

 All Possible Paths in DFS strategy are

Path - 1
        9,4
        8,4
        7,4
        6,4
        6,3
        6,2
        5,2
        4,2
        3,2
        2,2
        1,2
        1,3
        1,4
        0,4

Path - 2
        9,4
        8,4
        7,4
        6,4
        6,3
        6,2
        5,2
        4,2
        3,2
        2,2
        1,2
        1,3
        1,4
        1,5
        1,6
        2,6
        3,6
        4,6
        5,6
        6,6
        6,5

Path - 3
        6,5

 Feasible solution Paths in DFS strategy are

Path - 1
        9,4
        8,4
        7,4
        6,4
        6,3
        6,2
        5,2
        4,2
        3,2
        2,2
        1,2
        1,3
        1,4
        0,4

 **The Graph contains one or more cycles **
ASTAR algorithm in progress

ASTAR algorithm  ENDED

Graph Path Finder command Executed

 Feasible solution Path in ASTAR strategy is

Path - 1
        9,4
        8,4
        7,4
        6,4
        6,3
        6,2
        5,2
        4,2
        3,2
        2,2
        1,2
        1,3
        1,4
        0,4

 **The Graph contains one or more cycles ** 
 </pre>
  
    
  Feasible solution Path is the solution. The results can be more than 1 but the given problem has only one solution. Either starting from 0,4 or 9,7  
  
  
  
