/*
 *  In.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_IN_H_
#define _RETSU_CONDITION_IN_H_

#include "Base.h"

namespace Retsu {
	namespace Condition {
		class In : public Base {
		public:
      bool negation;
      vector<string> strvalues;
      vector<double> dblvalues;
			
			In(const string& column, const vector<string>& values) :
			Condition::Base::Base(column, Base::STRING) {
				this->strvalues = values;
				this->negation = false;
				this->type = Condition::Base::IN;
			}
			
			In(const string& column, const vector<string>& values, bool negation)  :
			Condition::Base::Base(column, Base::STRING) {
				this->strvalues = values;
				this->negation = negation;
				this->type = Condition::Base::IN;
			}
			
      In(const string& column, const vector<double>& values) :
			Condition::Base::Base(column, Base::NUMBER) {
				this->dblvalues = values;
				this->negation = false;
				this->type = Condition::Base::IN;
			}
			
			In(const string& column, const vector<double>& values, bool negation)  :
			Condition::Base::Base(column, Base::NUMBER) {
				this->dblvalues = values;
				this->negation = negation;
				this->type = Condition::Base::IN;
			}
      
      bool check(string& value) {
        vector<string>::iterator found;
        found = find(strvalues.begin(), strvalues.end(), value);
        
        if(found == strvalues.end()) {
          return false;
        } else {
          return true;
        }
      }
      
      // TODO implement this
      bool check(double& value) {
        return true;
      }
      
      void print(ostream& out) const {
        out << column << " IN (";
        for(size_t i = 0; i < strvalues.size(); i++) {
          out << strvalues[i];
          if(i < strvalues.size() - 1) out << ", "; 
        }
        out << ")";
      }
		};
	}
}

#endif