/*
 *  Gte.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_GTE_H_
#define _RETSU_CONDITION_GTE_H_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class Gte : public Base {
		public:
			string value;
			
			Gte(const string& column, const string& value) :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::GTE;
			}
      
      bool check(string& value) {
        return value >= this->value;
      }
      
      void print(ostream& out) const {
        out << column << " >= " << value;
      }
		};
	}
}

#endif