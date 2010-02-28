#include <Source/Table.h>

using namespace v8;
using namespace std;

int main(int argc, char * const argv[]) {
  // Create a handle scope to hold the temporary references.
  HandleScope handle_scope;
  
//  // Create a template for the global object where we set the
//  // built-in global functions.
//  Handle<ObjectTemplate> global = ObjectTemplate::New();
//  global->Set(String::New("log"), FunctionTemplate::New(LogCallback));
  
  // Each processor gets its own context so different processors
  // don't affect each other (ignore the first three lines).
  Persistent<Context> context = Context::New();
  
  // Enter the new context so all the following operations take place
  // within it.
  Context::Scope context_scope(context);
    
  Handle<String> source = String::New("5 + 2");
  
  // We're just about to compile the script; set up an error handler to
  // catch any exceptions the script might throw.
  TryCatch try_catch;
  
  // Compile the source code.
  Handle<Script> compiled_script = Script::Compile(source);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
//    Log(*error);
    // The script failed to compile; bail out.
    return 1;
  }
  
  // Run the script to get the result.
  Handle<Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    String::Utf8Value error(try_catch.Exception());
//    Log(*error);
    // Running the script failed; bail out.
    return false;
  }
  
  std::cout << *String::AsciiValue(result) << std::endl;
  
  // Dispose the persistent context.
  context.Dispose();
  
//  Retsu::Table domain("playback", ".");
//  
//  std::vector<Retsu::Record*> records;
//  
//  for(size_t i = 0; i < 1; i++) {
//    Retsu::Record* record = new Retsu::Record(i);
//    record->insert("duration", 10.50);
//    record->insert("action", "played");
//    record->insert("user_id", "00000001");
//    record->insert("session_id", "00000001");
//    records.push_back(record);
//  }
//  
//  boost::timer t;
//  
//  for(size_t j = 0; j < records.size(); j++) {
//    domain.insert(*records[j]);
//  }
//  
//  std::cout << "Completed in " << t.elapsed() << " seconds." << std::endl;
//  
//  for(size_t k = 0; k < records.size(); k++) {
//    delete(records[k]);
//  }  
  
  return 0;
}
