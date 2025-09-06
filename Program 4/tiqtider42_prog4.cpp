/*******************************************************************************************
    Filename: 	   tiqtider42_prog4.cpp
    Author: 	   Taseen Iqtider
    Date Created:  04/07/2025
    Date Updated:  04/19/2025
    Purpose: 	   Analyze a social network graph using an graph and BFS algorithm
    Reference:     Mrs. Crockett's example codes, program 1 code, pseudocode &
                   https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
                   https://www.geeksforgeeks.org/how-to-return-a-vector-from-a-function-in-cpp/
********************************************************************************************/

#include "GraphMatrix.h"

/***************************************
FUNCTION_NAME:     BFS() function
RETURN_TYPE:       vector of distances
****************************************/
vector<int> BFS(GraphMatrix &myMatrix, int start_person)
{
    // retrive number of vertices from the graph
    int numVertex = myMatrix.getNumVertices();

    // craete vector to track distance
    vector<int> distance(numVertex, -1);
    distance[start_person] = 0;

    // create a queue
    queue<int> matrixQueue;
    matrixQueue.push(start_person);

    // if the queue isn't empty
    while (!matrixQueue.empty())
    {
        // take & pop the first person outta the graph
        int curr = matrixQueue.front();
        matrixQueue.pop();

        // find connections between the people
        for (int i = 0; i < numVertex; i++)
        {
            if (myMatrix.isThereAnEdge(curr, i) && distance[i] == -1)
            {
                distance[i] = distance[curr] + 1;
                matrixQueue.push(i);
            }
        }
    }

    // return vector of distances
    return distance;
}

int main()
{
    // variable declaration
    string fileName, lineOfData;
    ifstream inputFile;
    int numVertices;
    int id1, id2;
    string line;

    cout << "\nWhat is the name of your text file that has your graph data (filename.txt)?\n";
    cout << "File: ";
    getline(cin, fileName);

    if (fileName == "graph2.txt")
    {
        cout << "\n\t\t[Br]eaking\n\t\t  [Ba]d\n";
    }
    // open the file
    inputFile.open(fileName);

    // read in the number of vertices
    inputFile >> numVertices;

    // create the matrix representation
    GraphMatrix myMatrix(numVertices);

    // create unordered map to map between names and IDs
    unordered_map<int, string> IDtoName;

    // add the vertices to the matrix (inspired by program 1)
    while (getline(inputFile, line))
    {
        // filter non-empty lines
        if (line.length() > 0)
        {
            int commaPos = line.find(','); // extract "0/April Crockett"
            string first = line.substr(0, commaPos);
            line.erase(0, commaPos + 1);

            // grab the rest of the string
            string second = line;

            // first person's ID and name
            int firstSlash = first.find('/');
            id1 = stoi(first.substr(0, firstSlash));
            string firstName = first.substr(firstSlash + 1);

            // second person's ID and name
            int secondSlash = second.find('/');
            id2 = stoi(second.substr(0, secondSlash));
            string secondName = second.substr(secondSlash + 1);

            // mapping IDs to names
            IDtoName[id1] = firstName;
            IDtoName[id2] = secondName;

            // adding edges to the matrix (graph is undirected, there's a 2-way connection)
            myMatrix.addEdge(id1, id2);
            myMatrix.addEdge(id2, id1);
        }
    }

    // close the file
    inputFile.close();

    // print the graph in 2D array
    cout << "\nResulting Graph Adjacency Matrix: \n\n";
    myMatrix.printGraph();

    // print the degree of separation matrix
    cout << "\n\nDegree of Separation Matrix:\n";
    int mostConnections = 0;
    int renownedID = -1;

    // formatting degree of separation matrix
    cout << "\t\t\t   ";
    for (int j = 0; j < numVertices; j++)
    {
        cout << setw(2) << j << " ";
    }
    cout << endl;
    cout << "\t\t\t   ";
    for (int j = 0; j < numVertices; j++)
    {
        cout << "---";
    }
    cout << endl;

    // print each person's name as a row label
    for (int i = 0; i < numVertices; i++)
    {
        cout << setw(25) << right << IDtoName[i] << "  ";
        // store the result from BFS in a list of distances
        vector<int> distance = BFS(myMatrix, i);

        // counter for 1st degree connection
        int firstDegConn = 0;

        for (unsigned int j = 0; j < distance.size(); j++)
        {
            // if no connectin, print dot
            if (distance[j] == -1)
            {
                cout << setw(2) << ". ";
            }
            // else print the degree of separation
            else
            {
                cout << setw(2) << distance[j] << " ";

                // increment the counter if the distance is 1
                if (distance[j] == 1)
                {
                    firstDegConn++;
                }
            }
        }
        cout << endl;

        // if current person is known to all, store the number & name
        if (firstDegConn > mostConnections)
        {
            mostConnections = firstDegConn;
            renownedID = i;
        }
    }

    // print the most well-known person
    cout << "\n\nThe most well-known person with the fewest degrees of separation from others is ";
    cout << IDtoName[renownedID] << " with " << mostConnections << " 1st degree connections in the social graph provided.\n";

    return 0;
}