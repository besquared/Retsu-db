/*
 *  Count.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Count.h"

Retsu::Aggregate::Count::Count(const string& measure) : 
Retsu::Aggregate::Base::Base(measure) {}

Retsu::Aggregate::Count::Count(const string& measure, const string& alias) :
Retsu::Aggregate::Base::Base(measure, alias) {}

std::string Retsu::Aggregate::Count::alias() {
	if(alias_.empty()) {
		return "count_" + measure;
	} else {
		return alias_;
	}
}

//void Aggregate::Count::apply(WorkSet& workset) {	
//	workset.aggregates[alias()] = workset.records.size();
//}

//void Aggregate::Count::apply(vector<WorkSet>& worksets) {
//	vector<WorkSet>::iterator workset;
//	for(workset = worksets.begin(); workset != worksets.end(); workset++) {
//		this->apply(*workset);
//	}
//}
