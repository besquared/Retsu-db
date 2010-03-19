/*
 *  EQ.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_EQ_H_
#define _RETSU_CONDITION_EQ_H_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class Eq : public Base {
		public:
			string value;
			
			Eq(const string& column, const string& value)  :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::EQ;
			}
      
      Eq(const string& column, const double& value) :
      Condition::Base::Base(column) {
        // need to store the double value here
        this->type = Condition::Base::EQ;
      }
			
      bool check(string& value) {
        return value == this->value;
      }
      
      bool check(double& value) {
        return false;
      }
      
      void print(ostream& out) const {
        out << column << " = " << value;
      }
		};
	}
}

#endif