# Study project
## The subject of algorithms and data structures

The goal of the project is to write a console application that reads a map in the form of symbols and in this map finds the shortest paths between given points.

More information about rules can be found in the rules.txt file

The solution was written in OOP style

Since it was forbidden to use containers from stl, I wrote my own implementations for the following structures:

- Hash map
- Priority queue
- Vector
- Pair

The BFS algorithm is used to convert the map in the form of symbols into a weighted graph, which guarantees to find the shortest path from the existing ones and also gives good performance.

To find the shortest path in a weighted graph, the Dijkstra algorithm is used in combination with priority queue, which increases its speed.

## Launching

The project was written in C++ language and uses CMake for building. To build the project, you need to have CMake installed on your computer

After compilation, you can run the application and test it by typing into the console according to the rules described in the rules.txt file. There is also a set of tests in the tests directory. To run them you can pass them as standard input to the program. By default, in the root directory execute the command:
```bash
$ build/proj2 < tests/<test_number>.in
```
And result will be displayed in console.