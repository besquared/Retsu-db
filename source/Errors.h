/*
 *  Errors.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/3/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_ERRORS_H_
#define _RETSU_ERRORS_H_

#include "Common.h"

namespace Retsu {
  using namespace std;
  
  class StorageError : public runtime_error {
  public:
    StorageError(const string& message);
  };
}

#endif