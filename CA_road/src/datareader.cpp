#include "datareader.h"

/*
    Reads a set of edges from a file in the following format: 
      <id> <start> <end> <weight>\n
    Params  filename: the name of the file to be read
            generate_log: generate a log file datareader.log if set to true, default to false
    Retval  a vector of Edge objects 
*/
vector<Edge> readEdges(string filename, bool generate_log) {
  ifstream edgeFile(filename); // input file
  string line; // buffer for each line
  vector<Edge> edgeVector; // vector to store the edges

  int idx; // store edge id
  int start; // store edge start vertex
  int end; // store edge end vertex
  double weight; // store edge weight
  int lineNumber = 0; // store current line number

  if (generate_log) {
    /* datareader.log is generated to check file sanity */
    string outputFilename = "datareader.log";
    ofstream outFile(outputFilename);

    if (edgeFile.is_open()){   //checking whether the file is open
        while(getline(edgeFile, line)){ //read data from file object and put it into string.

          lineNumber++;
          std::stringstream ss(line);

          if (!(ss >> idx >> start >> end >> weight)) {
            outFile << "Bad data at line " << lineNumber << ": " << line << std::endl;
            continue; // skip bad data
          }

          if (!ss.eof()) {
            outFile << "Bad data at line " << lineNumber << ": " << line << std::endl;
            continue; // skip bad data
          }
          
          Edge newEdge(idx, start, end, weight);
          edgeVector.push_back(newEdge);

        }

        edgeFile.close(); //close the file object.

        // record timestamp
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        outFile << "\nSuccessfully read " << filename << " at ";
        outFile << (now->tm_year + 1900) << '-' 
            << pad(to_string(now->tm_mon + 1)) << '-'
            <<  pad(to_string(now->tm_mday)) << ' '
            <<  pad(to_string(now->tm_hour)) << ':'
            <<  pad(to_string(now->tm_min)) << ':'
            <<  pad(to_string(now->tm_sec))
            << "\n";
        outFile.close();
    }
  } else {
    /* datareader.log is not generated */
    if (edgeFile.is_open()){   //checking whether the file is open
        while(getline(edgeFile, line)){ //read data from file object and put it into string.

          lineNumber++;
          std::stringstream ss(line);

          if (!(ss >> idx >> start >> end >> weight)) {
            continue; // skip bad data
          }

          if (!ss.eof()) {
            continue; // skip bad data
          }
          
          Edge newEdge(idx, start, end, weight);
          edgeVector.push_back(newEdge);

        }

        edgeFile.close(); //close the file object.
    }
  }
  return edgeVector;
}

std::string pad(std::string str, const char paddingChar)
{
    if(2 > str.size())
        str.insert(0, 2 - str.size(), paddingChar);
    return str;
}



void writeVertices(std::string filename, vector<int> path, vector<double> weightVector){
    if (path.empty() || weightVector.empty()) {
      std::cout << "Empty path, abort writing to file." << std::endl;
      return;
    }
    string folderName = "generated_paths/";
    string fileName = folderName + filename;
    std::ofstream outFile(fileName);
    int i = 0;
    // the important part
    outFile << "Vertex Idx" << "\t" << "Current Accumulated Length (km)"  << "\n";
    for (auto &e : path){
      if(i == 0){
        outFile << e << "\t \t" << std::to_string(0)  << "\n";
      }else{
        outFile << e << "\t \t" << std::to_string(weightVector[i-1])  << "\n";
      }
      i ++;
      
    } 
    outFile << "\n total length:" << "\t" << std::to_string(weightVector[weightVector.size()-1]);
    std::cout << "Path saved to " << folderName << filename << "." << std::endl;
}

vector<vector<double>> readVertices(string filename){
    ifstream vertexFile(filename); // input file
    string line; // buffer for each line
    vector<vector<double>> VertexVector; // vector to store the edges
    vector<double> X_coord;
    vector<double> Y_coord;

    int idx; // store edge id
    double x_coord; // x coord
    double y_coord; // store edge weight
    int lineNumber = 0; // store current line number
    
    if (vertexFile.is_open()){   //checking whether the file is open
        while(getline(vertexFile, line)){ //read data from file object and put it into string.

          lineNumber++;
          std::stringstream ss(line);

          if (!(ss >> idx >> x_coord >> y_coord)) {
            continue; // skip bad data
          }

          if (!ss.eof()) {
            continue; // skip bad data
          }
          
          X_coord.push_back((x_coord + 124.390) / 10.149);
          Y_coord.push_back(1 - ((y_coord - 32.5412) / 9.4760));

        }
        
        vertexFile.close(); //close the file object.
    }

    VertexVector.push_back(X_coord);
    VertexVector.push_back(Y_coord);
  return VertexVector;
}