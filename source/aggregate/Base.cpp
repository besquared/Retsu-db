/*
 *  Base.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */


#include "Base.h"

Retsu::Aggregate::Base::Base() {
	this->measure = "*";
	this->type = Retsu::Aggregate::Base::SINGLE;
}

Retsu::Aggregate::Base::Base(const string& measure) {
	this->measure = measure;
	this->type = Retsu::Aggregate::Base::SINGLE;
}

Retsu::Aggregate::Base::Base(const string& measure, const string& alias) {
	this->alias_ = alias;
	this->measure = measure;
	this->type = Retsu::Aggregate::Base::SINGLE;
}

// Some functions require more than one variable
Retsu::Aggregate::Base::Base(const vector<string>& measures, const string& alias) {
	this->alias_ = alias;
	this->measures = measures;
	this->type = Retsu::Aggregate::Base::MULTI;
}

void Retsu::Aggregate::Base::measure_names(set<string>& results) {
	if(this->type == Retsu::Aggregate::Base::SINGLE) {
		results.insert(measure);
	} else {
		results.insert(measures.begin(), measures.end());
	}
}