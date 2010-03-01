#include <Source/Table.h>

using namespace v8;
using namespace std;

Handle<Value> table_insert(const Arguments& args) {
  if(args.Length() < 1) {
    return Boolean::New(false);
  } else {
    if(!args[0]->IsObject()) {
      return Boolean::New(false);
    } else {
      Local<Object> values = args[0]->ToObject();
      Local<Array> dimensions = values->GetPropertyNames();
      
      for(size_t i = 0; i < dimensions->Length(); i++) {
        Local<Number> index = Number::New(i);
        Local<Value> key = dimensions->Get(index);
        Local<Value> val = values->Get(key);
//        cout << "Got " << *String::AsciiValue(key) << " => " << *String::AsciiValue(val) << endl;
      }
      
      return Boolean::New(true);
    }
  }
}

Handle<Value> table_get(Local<String> name, const AccessorInfo &info) {
  Handle<ObjectTemplate> table_templ = ObjectTemplate::New();
  table_templ->Set("name", name);
  table_templ->Set("insert", FunctionTemplate::New(table_insert));
  return table_templ->NewInstance();
}

int main(int argc, char * const argv[]) {
  // Create a handle scope to hold the temporary references.
  HandleScope handle_scope;
    
  Handle<ObjectTemplate> db_template = ObjectTemplate::New();
  db_template->SetNamedPropertyHandler(table_get);
  
  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("db"), db_template);
  
  Persistent<Context> context = Context::New(NULL, global);
  
  Context::Scope context_scope(context);

  Handle<String> source = String::New("\
    var playback = db.playback;\
    for(var i = 0; i < 100000; i++) {\
      playback.insert(\
        {'mykey': 'myval', 'anotherkey': 'anothervalue'}\
      );\
    }");
  
  // We're just about to compile the script; set up an error handler to
  // catch any exceptions the script might throw.
  TryCatch try_catch;
  
  // Compile the source code.
  Handle<Script> compiled_script = Script::Compile(source);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    // The script failed to compile; bail out.
    return 1;
  }
  
  // Run the script to get the result.

  boost::timer t;
  Handle<Value> result = compiled_script->Run();
  cout << "Completed in " << t.elapsed() << " seconds." << endl;

  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    String::Utf8Value error(try_catch.Exception());
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
