/*
 *  Nneq.h
 *  flow
 *
 *  Created by Josh Ferguson on 2/1/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_NEQ_H_
#define _RETSU_CONDITION_NEQ_H_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class Neq : public Base {
		public:
			string value;
			
			Neq(const string& column, const string& value)  :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::EQ;
			}
						
      bool check(string& value) {
        return value != this->value;
      }
      
      void print(ostream& out) const {
        out << column << " != " << value;
      }      
		};
	}
}

#endif