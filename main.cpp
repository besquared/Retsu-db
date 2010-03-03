#include <source/Commander.h>

using namespace v8;
using namespace std;

int main(int argc, char * const argv[]) {  
  Retsu::Commander* commander = new Retsu::Commander();
  
  boost::timer t;
  
  commander->execute("db.playback.create();");
  
  commander->execute("\
    var playback = db.playback;\
    for(var i = 0; i < 70000; i++) {\
      playback.insert(\
        {'00000000': 'another thing'}\
      );\
    }"
  );
  
  std::cout << "Executed in " << t.elapsed() << " seconds" << std::endl;
  
  t.restart();
  
  Handle<Value> result = commander->execute("db.playback.lookup(100, '00000000');");

  std::cout << "Executed in " << t.elapsed() << " seconds" << std::endl;

  cout << *String::AsciiValue(result) << endl;
  
  delete(commander);
  
  return 0;
}
