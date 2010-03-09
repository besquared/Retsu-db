/*
 *  Conditions.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/1/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Conditions.h"

void Retsu::Conditions::eq(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Eq(name, value)));
}

void Retsu::Conditions::neq(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Neq(name, value)));
}

void Retsu::Conditions::gt(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gt(name, value)));
}

void Retsu::Conditions::gte(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gte(name, value)));
}

void Retsu::Conditions::lt(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lt(name, value)));
}

void Retsu::Conditions::lte(const string& name, const string& value) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lte(name, value)));
}

void Retsu::Conditions::in(const string& name, const vector<string>& values) {
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::In(name, values)));
}

/*
 * Application
 */

bool Retsu::Conditions::check(const string& column, string& value) const {
  shared_ptr<Condition::Base> condition;
	for(size_t i = 0; i < conditions.size(); i++) {
		condition = conditions[i];
		if(condition != NULL && condition->column == column) {
			if(!condition->check(value)) {
        return false;
      }
		}
	}
  
  return true;
}

void Retsu::Conditions::apply(const string& column, vector<string>& values) const {
	shared_ptr<Condition::Base> condition;
	for(size_t i = 0; i < conditions.size(); i++) {
		condition = conditions[i];
		if(condition != NULL && condition->column == column) {
			condition->apply(values);
		}
	}
}