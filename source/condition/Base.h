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

#include "Common.h"

namespace Retsu {
	namespace Condition {
    using namespace std;      

		class Base {
		public:
      enum ValueType { STRING, NUMBER };
			enum ConditionType { EQ, GT, GTE, LT, LTE, IN };

			string column;
			ConditionType type;
      ValueType value_type;

			Base(const string& column) {
				this->column = column;
        this->value_type = STRING;
			}
      
      Base(const string& column, ValueType value_type) {
        this->column = column;
        this->value_type = value_type;
      }
			
      virtual bool check(string& value) = 0;
      virtual bool check(double& value) = 0;
      
      bool check(void* datum, int vsize) {
        if(value_type == Base::STRING) {
          string value;
          intern(datum, vsize, value);
          return check(value);
        } else {
          double value;
          intern(datum, vsize, value);
          return check(value);
        }
      }      
      
      void intern(void* value, int vsize, string& result) {
        result = string((char*)value, (size_t)vsize);
      }
      
      void intern(void* value, int vsize, double& result) {
        if(vsize == sizeof(double)) {
          result = *((double*)value);
        }
      }
      
      virtual void print(ostream& out) const = 0;
      friend ostream& operator<<(ostream& out, const Base& condition) {
        condition.print(out);
        return out;
      }
		};
	}
}

#endif