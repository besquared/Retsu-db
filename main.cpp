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
      source += line + "\n";
    }
    source_file.close();
  }
  
  return source;
}

int main(int argc, char * const argv[]) { 
  Retsu::Commander* commander = new Retsu::Commander();
  
  string source_file = "estimate.js";
  string source = read_source(source_file);
  
  cout << "Executing " << source_file << "\n\n" << source << endl;
  
  cout << "-------------------------------------------------\n\n";
  
  boost::timer t;
  commander->execute(source);
  std::cout << "Executed in " << t.elapsed() << " seconds" << std::endl;
  
  delete(commander);
  
  return 0;
}
