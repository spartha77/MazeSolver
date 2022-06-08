<pre>
Maze solver : Running the test cases
-------------------------------------

The executable is built for Windows platform.
Please refer to the spreadsheet Mazes.xlsxMazes.xlsx for better display of
the mazes (test cases) and their paths

Usage: (The command line arguments are files that contains the definition of the maze (graph).
-----------------------------------------------------------------------------------------------

// To solve the maze for the given problem
MazeSolver.exe maze_01_given_sample.txt



// To solve the maze that contains two connected components
MazeSolver.exe maze_02_2_connected_components.txt



// To solve a maze (graph) that contains one or more cycles:
// The maze solver will identify the presence of cycles but both the
// Depth Serach Strategy and Non Greedy A* strategy will pick only one 
// path that is not a part of another path's cycle

// The maze solver will identify cycles as follows
**The Graph contains one or more cycles **

MazeSolver.exe maze_02_2_connected_components.txt


// The following maze contains cycle and the path along has equal weights (total weights of the path). 
//SO the A* picks one of the path. The DFS also picks one of the path.
// The maze solver will identify cycles as follows
**The Graph contains one or more cycles **

mazeSolver.exe maze_04_loop_equal_weights_ASTAR.txt


What to look for? 
------------------

Output from DFS will look like below for running
MazeSolver.exe maze_04_loop_equal_weights_ASTAR.txt
----------------------------------------------------

Please have a look at the standard output (console) for the results. They will be displayed as 


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
 
 
 Output from Non Greedy A* will look like below.
 
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
