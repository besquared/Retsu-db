/*
 *  CommonOperations.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/4/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "CommonOperations.h"

/*
 * Installation and global commands
 */
void Retsu::CommonOperations::install(Handle<ObjectTemplate> scope) {
  scope->Set(String::New("print"), FunctionTemplate::New(print));
}

v8::Handle<v8::Value> Retsu::CommonOperations::print(const Arguments& args) {
  for(size_t i = 0; i < args.Length(); i++) {
    cout << *String::AsciiValue(args[i]->ToString()) << endl;
  }
  return Handle<Value>();
}
