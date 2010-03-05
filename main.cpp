#include <source/Commander.h>

using namespace v8;
using namespace std;

string read_source(const string& path) {
  string line;
  string source;
  
  ifstream source_file(path.c_str());
  
  if(source_file.is_open()) {
    while(!source_file.eof()) {
      getline(source_file, line);
      source += line;
    }
    source_file.close();
  }
  
  return source;
}

int main(int argc, char * const argv[]) {  
  Retsu::Commander* commander = new Retsu::Commander();
  
  string source = read_source("create.js");
  
  cout << source << endl;
  
  boost::timer t;
    
  std::cout << "Executed in " << t.elapsed() << " seconds" << std::endl;
    
  delete(commander);
  
  return 0;
}
