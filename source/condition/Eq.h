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
			string strvalue;
			double dblvalue;
      
			Eq(const string& column, const string& value)  :
			Condition::Base::Base(column, Base::STRING) {
				this->strvalue = value;
				this->type = Base::EQ;
        cout << "Instantiating string conditional EQ " << column << " => " << value << endl;
			}
      
      Eq(const string& column, const double& value) :
      Condition::Base::Base(column, Base::NUMBER) {
        this->dblvalue = value;
        this->type = Base::EQ;
      }
			
      bool check(string& value) {
        cout << "Checking " << column << value << " == " << strvalue << endl;
        return value == strvalue;
      }
      
      bool check(double& value) {
        cout << "Checking " << column << value << " == " << strvalue << endl;
        return value == dblvalue;
      }
            
      void print(ostream& out) const {
        out << column << " = " << strvalue;
      }
		};
	}
}

#endif