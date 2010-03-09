/*
 *  Condition.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITION_BASE_H_
#define _RETSU_CONDITION_BASE_H_

#include <Common.h>

namespace Retsu {
	namespace Condition {
    using namespace std;      

		class Base {
		public:
			enum ConditionType { EQ, GT, GTE, LT, LTE, IN };

			string column;
			ConditionType type;
			
			Base(const string& column) {
				this->column = column;
			}
			
      virtual bool check(string& value) = 0;
			virtual void apply(vector<string>& values) = 0;
      virtual void print(ostream& out) const = 0;
      
      friend ostream& operator<<(ostream& out, const Base& condition) {
        condition.print(out);
        return out;
      }
		};
	}
}

#endif