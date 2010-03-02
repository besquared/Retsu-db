#include <source/Commander.h>

using namespace v8;
using namespace std;

int main(int argc, char * const argv[]) {  
  Retsu::Commander* commander = new Retsu::Commander();
  
  boost::timer t;
  
  commander->execute("\
    db.playback.create();\
    var playback = db.playback;\
    for(var i = 0; i < 70000; i++) {\
      playback.insert(\
        {'00000000': '00000000'}\
      );\
    }"
  );  
  
  std::cout << "Executed in " << t.elapsed() << " seconds" << std::endl;
  
  delete(commander);
  
  return 0;
}
