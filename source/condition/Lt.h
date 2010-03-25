/*
 *  Lt.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_LT_H_
#define _flow_condition_lt_h_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class Lt : public Base {
		public:
			string strvalue;
      double dblvalue;
			
			Lt(const string& column, const string& value) :
			Condition::Base::Base(column, Base::STRING) {
				this->strvalue = value;
				this->type = Condition::Base::LT;
			}
      
      Lt(const string& column, const double& value) :
			Condition::Base::Base(column, Base::NUMBER) {
				this->dblvalue = value;
				this->type = Condition::Base::LT;
			}			
			
      bool check(string& value) {
        return value < strvalue;
      }
      
      bool check(double& value) {
        return value < dblvalue;
      }
      
      void print(ostream& out) const {
        out << column << " < " << strvalue;
      }      
		};
	}
}

#endif