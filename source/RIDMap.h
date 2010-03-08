/*
 *  RIDMap.h
 *  retsu
 *
 *  Created by Josh Ferguson on 12/19/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_RIDMAP_H_
#define _RETSU_RIDMAP_H_

#include "Common.h"
#include "RIDList.h"

namespace Retsu {
  typedef std::map<std::string, RIDList> RIDMap;
}

#endif