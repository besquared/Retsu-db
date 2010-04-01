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

void Retsu::Conditions::add(const string& type, const string& column, const string& value) {
  if(type == "eq") {
    eq(column, value);
  } else if(type == "neq") {
    neq(column, value);
  } else if(type == "gt") {
    gt(column, value);
  } else if(type == "gte") {
    gte(column, value);
  } else if(type == "lt") {
    lt(column, value);
  } else if(type == "lte") {
    lte(column, value); 
  } else if(type == "in") {
    // this could be an array of strings or numbers
    // do some in stuff here, unwrap the array and whatnot
  }
}

void Retsu::Conditions::add(const string& type, const string& column, const double& value) {
  if(type == "eq") {
    eq(column, value);
  } else if(type == "neq") {
    neq(column, value);
  } else if(type == "gt") {
    gt(column, value);
  } else if(type == "gte") {
    gte(column, value);
  } else if(type == "lt") {
    lt(column, value);
  } else if(type == "lte") {
    lte(column, value); 
  } else if(type == "in") {
    // this could be an array of strings or numbers
    // do some in stuff here, unwrap the array and whatnot
  }  
}

/*
 * Application
 */

bool Retsu::Conditions::check(const string& column, string& value) const {
	for(size_t i = 0; i < conditions.size(); i++) {
		if(conditions[i]->column == column && !conditions[i]->check(value)) {
      return false;
		}
	}
  
  return true;
}

bool Retsu::Conditions::check(const string& column, void* datum, int vsize) const {  
  for(size_t i = 0; i < conditions.size(); i++) {
		if(conditions[i]->column == column && !conditions[i]->check(datum, vsize)) {
      return false;
		}
	}
  
  return true;  
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
