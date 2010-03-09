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
			string value;
			
			Lt(const string& column, const string& value) :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::LT;
			}			
			
      bool check(string& value) {
        return value < this->value;
      }      
      
			void apply(vector<string>& values) {
				vector<string> results;
				results.reserve(values.size());
				size_t vsize = values.size();
				for(size_t i = 0; i < vsize; i++) {
					if(this->check(values[i])) {
						results.push_back(values[i]);
					}
				}
				values = results;
			}
      
      void print(ostream& out) const {
        out << column << " < " << value;
      }      
		};
	}
}

#endif