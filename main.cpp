#include <source/Commander.h>

using namespace v8;
using namespace std;

int main(int argc, char * const argv[]) {  
  Retsu::Commander* commander = new Retsu::Commander();
  
  /*
//  commander->execute("\
//    db.playback.create();\
//    var playback = db.playback;\
//    for(var i = 0; i < 10000; i++) {\
//      playback.insert(\
//        {'mykey': 'myval', 'anotherkey': 'anothervalue'}\
//      );\
//    }");
  */
  
  commander->execute("2+2");
  
  delete(commander);
  
  return 0;
}
