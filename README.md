# Banker's Algorithm in C++

Banker's Algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the allocation for predetermined maximum possible amounts of all resources <br>
Some of the features included in this code are:
  - Class implemented Resource and Process
  - Auto data generation
  - User defined number of processes and resources

## Example
Consider an example <br>
 * There are five processes and three resources.
 * Processes named as 0,1,2,3,4
 * Resources named as A,B,C
 * Maximum instances of resource A->10, B->5, C->7
 * Process allocation is as follows initially:
 
| Process |   Allocation  | Max Requirement |      Need     | Currently Available |
|:-------:|:-------------:|:---------------:|:-------------:|:-------------------:|
|         | A     B     C |  A     B     C  | A     B     C |    A     B     C    |
|    0    | 0     1     0 |  7     5     3  | 7     4     3 |    3     3     2    |
|    1    | 2     0     0 |  3     2     2  | 1     2     2 |                     |
|    2    | 3     0     2 |  9     0     2  | 6     0     0 |                     |
|    3    | 2     1     1 |  2     2     2  | 0     1     1 |                     |
|    4    | 0     0     2 |  4     3     3  | 4     3     1 |                     |


After applying banker's algorithm, we come to know that the safe sequence exists viz. <br>
Safe sequence of process execution: <1,3,4,0,2>
To learn more, [click here](https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/)