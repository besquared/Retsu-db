/*
 *  Errors.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/3/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Errors.h"

Retsu::StorageError::StorageError(const string& message) : runtime_error(message) {}