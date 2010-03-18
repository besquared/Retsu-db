/*
 *  Conditions.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CONDITIONS_H_
#define _RETSU_CONDITIONS_H_

#include "Common.h"
#include "Condition/Base.h"
#include "Condition/Eq.h"
#include "Condition/Neq.h"
#include "Condition/In.h"
#include "Condition/Gt.h"
#include "Condition/Gte.h"
#include "Condition/Lt.h"
#include "Condition/Lte.h"

namespace Retsu {  
  using namespace std;
  using namespace boost;
  
  class Conditions {
  protected:
    vector< shared_ptr<Condition::Base> > conditions;
    
  public:
    set<string> columns;

		/*
		 * Shortcuts
		 */
		void eq(const string& name, const string& value);
    void neq(const string& name, const string& value);
		void gt(const string& name, const string& value);
		void gte(const string& name, const string& value);
		void lt(const string& name, const string& value);
		void lte(const string& name, const string& value);
		void in(const string& name, const vector<string>& value);
    
		/*
		 * Application
		 */
    bool check(const string& column, string& value) const;
		void apply(const string& column, vector<string>& values) const;
    
    /*
     * Introspect
     */
    size_t size() const;
    bool empty() const;
  };
}

#endif