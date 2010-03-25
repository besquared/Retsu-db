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
			string strvalue;
			double dblvalue;
      
			Neq(const string& column, const string& value)  :
			Condition::Base::Base(column, Base::STRING) {
				this->strvalue = value;
				this->type = Condition::Base::EQ;
			}

      Neq(const string& column, const double& value)  :
			Condition::Base::Base(column, Base::NUMBER) {
				this->dblvalue = value;
				this->type = Condition::Base::EQ;
			}
      
      bool check(string& value) {
        return value != strvalue;
      }
      
      bool check(double& value) {
        return value != dblvalue;
      }
      
      void print(ostream& out) const {
        out << column << " != " << strvalue;
      }      
		};
	}
}

#endif