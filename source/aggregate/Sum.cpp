/*
 *  Sum.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Sum.h"

Retsu::Aggregate::Sum::Sum(const string& measure) : 
Retsu::Aggregate::Base::Base(measure) {}

Retsu::Aggregate::Sum::Sum(const string& measure, const string& alias) :
Retsu::Aggregate::Base::Base(measure, alias) {}

std::string Retsu::Aggregate::Sum::alias() {
	if(alias_.empty()) {
		return "sum_" + measure;
	} else {
		return alias_;
	}
}

//void Retsu::Aggregate::Sum::apply(WorkSet& workset) {
//	double sum = 0;
//	vector<double>::iterator value;
//	vector<double> values = workset.measures[measure];
//	for(value = values.begin(); value != values.end(); value++) {
//		sum += *value;
//	}
//	workset.aggregates[alias()] = sum;
//}
//
//void Retsu::Aggregate::Sum::apply(vector<WorkSet>& worksets) {
//	vector<WorkSet>::iterator workset;
//	for(workset = worksets.begin(); workset != worksets.end(); workset++) {
//		this->apply(*workset);
//	}
//}