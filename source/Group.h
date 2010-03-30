/*
 *  Group.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_GROUP_H_
#define _RETSU_GROUP_H_

#include "Common.h"
#include "Table.h"
#include "RIDList.h"

namespace Retsu {
  class Group {
  public:
    RIDList records;
  };
}

#endif