#include <Source/Commander.h>

using namespace v8;
using namespace std;

int main(int argc, char * const argv[]) {
  HandleScope handle_scope;
  
  Handle<ObjectTemplate> db = ObjectTemplate::New();
  db->SetNamedPropertyHandler(Retsu::cmd_table);
  
  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("db"), db);
  
  Persistent<Context> context = Context::New(NULL, global);
  Context::Scope context_scope(context);

  Handle<String> script = String::New("2+2");
  
  Handle<Script> compiled_script = Script::Compile(script);
  Handle<Value> result = compiled_script->Run();
  
  
//  Retsu::Commander* commander = new Retsu::Commander();
//  
////  commander->execute("\
////    db.playback.create();\
////    var playback = db.playback;\
////    for(var i = 0; i < 10000; i++) {\
////      playback.insert(\
////        {'mykey': 'myval', 'anotherkey': 'anothervalue'}\
////      );\
////    }");
//  
//  commander->execute("2+2");
//  
//  delete(commander);
  
  return 0;
}
