#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <list>
#include <stdint.h>

using namespace std;
#endif /* __PROGTEST__ */

class FileHandler {
    ifstream * inFile;
    ofstream * outFile;
    
    const int type;
    
public:
    static const int READ = 1;
    static const int WRITE = 0;
    
    FileHandler(const char * fileName, const int type): inFile(NULL), outFile(NULL), type(type) {
        if(this->type == FileHandler::READ) {
            inFile = new ifstream(fileName);
            return;
        }
        
        outFile = new ofstream(fileName);
    }
    
    string readLine() {
        string line = "";
        
        getline(*inFile, line);
        
        return line;
    }
    
    void write(const string & str) {
        *outFile << str;
    }
    
    void close() {
        if(inFile != NULL && inFile->is_open())
            inFile->close();
        
        if(outFile != NULL && outFile->is_open())
            outFile->close();
    }
    
    ~FileHandler() {
        if(inFile != NULL)
            delete inFile;
        
        if(outFile != NULL)
            delete outFile;
    }
};


class DataLoader {
    
    
public:
    
};

class Graph {
    int roomsCount;
    int lecturesCount;
    
public:
    
};

int readDigit(int & pos, const string & str) {
    string tmp = "";
    
    for (; pos < (int) str.length(); ++pos) {
        char c = str.at(pos);
        
        if(!isdigit(c)) break;
        
        tmp += c;
    }
    
    return stoi(tmp);
}

void rozvrh( const char * inFile, const char * outFile ) {
    int n, m, pos = 0;
    
    FileHandler file(inFile, FileHandler::READ);
    
    string line = file.readLine();
    string tmp;
    
    n = readDigit(pos, line);
    m = readDigit(pos, line);
    
    
}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    rozvrh("t01", "t01o");
    return 0;
}
#endif /* __PROGTEST__ */
