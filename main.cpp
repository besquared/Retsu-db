#include <Source/Table.h>
#include <Source/TableOperations.h>

using namespace v8;
using namespace std;

void dump_v8_object(Local<Object> object) {
  Local<Array> keys = object->GetPropertyNames();
  
  for(size_t i = 0; i < keys->Length(); i++) {
    Local<Number> index = Number::New(i);
    Local<Value> key = keys->Get(index);
    Local<Value> value = object->Get(key);
    
    cout << *String::AsciiValue(key) << " => " << *String::AsciiValue(value) << endl;
  }
}

Handle<Value> table_get(Local<String> name, const AccessorInfo &info) {
  Handle<ObjectTemplate> table_templ = ObjectTemplate::New();
  
  table_templ->Set("name", name);
  table_templ->Set("insert", FunctionTemplate::New(Retsu::TableOperations::insert));
  
  return table_templ->NewInstance();
}

int main(int argc, char * const argv[]) {
  HandleScope handle_scope;
    
  Handle<ObjectTemplate> db_template = ObjectTemplate::New();
  db_template->SetNamedPropertyHandler(table_get);
  
  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("db"), db_template);
  
  Persistent<Context> context = Context::New(NULL, global);
  
  Context::Scope context_scope(context);

  Handle<String> source = String::New("\
    var playback = db.playback;\
    for(var i = 0; i < 1; i++) {\
      playback.insert(\
        {'mykey': 'myval', 'anotherkey': 'anothervalue'}\
      );\
    }");
  
  TryCatch try_catch;
  
  Handle<Script> compiled_script = Script::Compile(source);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    return 1;
  }

  boost::timer t;
  Handle<Value> result = compiled_script->Run();
  cout << "Completed in " << t.elapsed() << " seconds." << endl;

  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    return false;
  }
  
  std::cout << *String::AsciiValue(result) << std::endl;
  
  context.Dispose();
    
  return 0;
}
