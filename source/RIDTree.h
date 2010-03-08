/*
 *  RIDTree.h
 *  retsu
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_RIDTREE_H_
#define _RETSU_RIDTREE_H_

#include "Common.h"
#include "RIDMap.h"

namespace Retsu {
  typedef std::map<std::string, RIDMap> RIDTree;
}

#endif