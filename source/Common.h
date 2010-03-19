/*
 *  Common.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSUDB_COMMON_H_
#define _RETSUDB_COMMON_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <tcutil.h>
#include <tcbdb.h>
#include <tcfdb.h>

#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <include/v8.h>

namespace fs = boost::filesystem;

typedef double RecordID;

#endif