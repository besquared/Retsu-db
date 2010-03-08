/*
 *  Gte.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _flow_condition_gte_h_
#define _flow_condition_gte_h_

#include "Base.h"

namespace Flow {
	namespace Condition {
		class Gte : public Condition::Base {
		public:
			string value;
			
			Gte(const string& column, const string& value) :
			Condition::Base::Base(column) {
				this->value = value;
				this->type = Condition::Base::GTE;
			}
      
      bool Check(string& value) {
        return value >= this->value;
      }
      
			void Apply(vector<string>& values)  {
				vector<string> results;
				results.reserve(values.size());
				size_t vsize = values.size();
				for(size_t i = 0; i < vsize; i++) {
					if(this->Check(values[i])) {
						results.push_back(values[i]);
					}
				}
				values = results;
			}
      
      void print(ostream& out) const {
        out << column << " >= " << value;
      }      
		};
	}
}

#endif