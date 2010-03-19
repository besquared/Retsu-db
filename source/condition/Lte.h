/*
 *  Lte.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_LTE_H_
#define _RETSU_CONDITION_LTE_H_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class Lte : public Base {
		public:
			string value;
			
			Lte(const string& column, const string& value) :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::LTE;
			}
			
      bool check(string& value) {
        return value <= this->value;
      }      
      
      void print(ostream& out) const {
        out << column << " <= " << value;
      }      
		};
	}
}

#endif