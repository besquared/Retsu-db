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
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Eq(name, value)));
}

void Retsu::Conditions::eq(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Eq(name, value)));
}

void Retsu::Conditions::neq(const string& name, const string& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Neq(name, value)));
}

void Retsu::Conditions::neq(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Neq(name, value)));
}

void Retsu::Conditions::gt(const string& name, const string& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gt(name, value)));
}

void Retsu::Conditions::gt(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gt(name, value)));
}

void Retsu::Conditions::gte(const string& name, const string& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gte(name, value)));
}

void Retsu::Conditions::gte(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Gte(name, value)));
}

void Retsu::Conditions::lt(const string& name, const string& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lt(name, value)));
}

void Retsu::Conditions::lt(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lt(name, value)));
}

void Retsu::Conditions::lte(const string& name, const string& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lte(name, value)));
}

void Retsu::Conditions::lte(const string& name, const double& value) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::Lte(name, value)));
}

void Retsu::Conditions::in(const string& name, const vector<string>& values) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::In(name, values)));
}

void Retsu::Conditions::in(const string& name, const vector<double>& values) {
  columns.insert(name);
	conditions.push_back(shared_ptr<Condition::Base>(new Condition::In(name, values)));
}

/*
 * Application
 */

bool Retsu::Conditions::check(const string& column, string& value) const {
	for(size_t i = 0; i < conditions.size(); i++) {
		if(conditions[i] != NULL && conditions[i]->column == column) {
			if(!conditions[i]->check(value)) {
        return false;
      }
		}
	}
  
  return true;
}

Retsu::Condition::Base::ValueType Retsu::Conditions::value_type(const string& column) const {
  // get the value type of the conditioned columns
}

/*
 * Introspection
 */

size_t Retsu::Conditions::size() const {
  return conditions.size();
}

bool Retsu::Conditions::empty() const {
  return conditions.empty();
}
