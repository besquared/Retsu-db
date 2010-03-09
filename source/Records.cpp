/*
 *  Records.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/3/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Records.h"

Retsu::Records::Records(const fs::path& table_path) {
  this->database = tcfdbnew();
  this->table_path = table_path;
}

Retsu::Records::~Records() {
  this->close();
  tcfdbdel(database);
}

/*
 * I/O Management
 */

std::string Retsu::Records::path() {
  return table_path.string() + "/records.tcf";
}

void Retsu::Records::close() {
  if(!tcfdbclose(database)) {
    // throw StorageError("Could not close records database at " + Path());
  }
}

void Retsu::Records::truncate() {
	if(!open(FDBOWRITER | FDBOTRUNC)) {
		close();
	} else {
		throw StorageError("Could not truncate records database at " + path());
	}	
}

void Retsu::Records::open_reader() {
  if(!open(FDBOREADER)) {
    throw StorageError("Could not open records for reading at " + path());
  }
}

void Retsu::Records::open_writer() {
  if(!open(FDBOWRITER | FDBOCREAT)) {
    throw StorageError("Could not open records for writing at " + path());
  }
}

bool Retsu::Records::open(int mode) {
	return tcfdbopen(database, path().c_str(), mode);
}

void Retsu::Records::create(const fs::path& table_path) {
  TCFDB* database = tcfdbnew();
  string full_path = (table_path / fs::path("records.tcf")).string();
  
	tcfdbtune(database, sizeof(double), INT_MAX);	
	if(!tcfdbopen(database, full_path.c_str(), FDBOCREAT)) {
    throw StorageError("Could not create records database at " + full_path);
	} else {
    tcfdbclose(database);
    tcfdbdel(database);
  }
}

void Retsu::Records::cursor_init() {
  if(!tcfdbiterinit(database)) {
    throw StorageError("Could not instantiate records iterator for each in " + path());
  }
}

uint64_t Retsu::Records::cursor_next() {
  return tcfdbiternext(database);
}

void Retsu::Records::insert(const RecordID& key) {
  double new_value = tcfdbadddouble(database, key, FDBIDNEXT);
  
  if(isnan(new_value)) {
    throw StorageError("Could not insert into records database key => " + 
                       boost::lexical_cast<string>(key) + ". " + tcfdberrmsg(tcfdbecode(database)));
  }
}

uint64_t Retsu::Records::size() {
  return tcfdbrnum(database);
}
