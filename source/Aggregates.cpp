/*
 *  Aggregates.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Aggregates.h"

void Retsu::Aggregates::sum(const string& name) {
	aggregates.push_back(shared_ptr<Aggregate::Sum>(new Aggregate::Sum(name)));
}

void Retsu::Aggregates::count(const string& name) {
	aggregates.push_back(shared_ptr<Aggregate::Count>(new Aggregate::Count(name)));
}

//void Retsu::Aggregates::apply(vector<WorkSet>& worksets) {
//	for(size_t i = 0; i < size(); i++) {
//		this->at(i)->apply(worksets);
//	}	
//}

void Retsu::Aggregates::measure_names(set<string>& results) {
	set<string> measures;
	for(size_t i = 0; i < aggregates.size(); i++) {
		aggregates[i]->measure_names(measures);
		results.insert(measures.begin(), measures.end());
	}
}

// Set of output dimensions
std::set<std::string> Retsu::Aggregates::aliases() {
  set<string> results;
  
  for(size_t i = 0; i < size(); i++) {
		results.insert(Aggregates[i]->alias());
	}
  
  return results;
}