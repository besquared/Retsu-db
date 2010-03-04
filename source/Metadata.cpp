/*
 *  Metadata.cpp
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Metadata.h"

Retsu::Metadata::Metadata(const fs::path& table_path) {
	this->table_path = table_path;
	this->database = tcbdbnew();
}

Retsu::Metadata::~Metadata() {
	this->Close();
  tcbdbdel(this->database);
}

bool Retsu::Metadata::Create(const fs::path& table_path) {
	TCBDB* database = tcbdbnew();
	
	tcbdbtune(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(database, Retsu::Metadata::Path(table_path).c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(database);
		tcbdbdel(database);
		return true;
	} else {
		tcbdbdel(database);
		return false;
	}
}

std::string Retsu::Metadata::Path(const fs::path& table_path) {
  return (table_path / fs::path("metadata.tcb")).string();
}

bool Retsu::Metadata::OpenReader() {
  return this->Open(BDBOREADER);
}

bool Retsu::Metadata::OpenWriter() {
  return this->Open(BDBOWRITER | BDBOCREAT);
}

bool Retsu::Metadata::Truncate() {
	if(this->Open(BDBOWRITER | BDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}
}

bool Retsu::Metadata::Open(int mode) {
	return tcbdbopen(this->database, Retsu::Metadata::Path(this->table_path).c_str(), mode);
}

bool Retsu::Metadata::Close() {
	if(tcbdbrnum(this->database) % (1<<16) == 0) {
		tcbdboptimize(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	}
	
	return tcbdbclose(this->database);
}

bool Retsu::Metadata::Get(const string& key, string& result) {
	int b_size;
	void* buffer;
	
	buffer = tcbdbget(this->database, key.c_str(), key.size(), &b_size);
	
	if(buffer == NULL) {
		return false;
	} else {
		result.assign((char*)buffer, b_size);
		free(buffer);
		return true;
	}
}

bool Retsu::Metadata::Get(const string& key, set<string>& results) {
	TCLIST* values = tcbdbget4(this->database, key.c_str(), key.size());
	
	if(values != NULL) {
		const char* value;
		size_t list_size = tclistnum(values);
    for(size_t i = 0; i < list_size; i++) {
			value = tclistval2(values, i);
			if(value != NULL) { results.insert(value); }
    }
    tclistdel(values);
		return true;
  } else {
		return false;
	}
}

bool Retsu::Metadata::Get(const string& key, vector<string>& results) {
	TCLIST* values = tcbdbget4(this->database, key.c_str(), key.size());
	
	if(values != NULL) {
		const char* value;
		size_t list_size = tclistnum(values);
    for(size_t i = 0; i < list_size; i++) {
			value = tclistval2(values, i);
			if(value != NULL) { results.push_back(value); }
    }
    tclistdel(values);
		return true;
  } else {
		return false;
	}
}

bool Retsu::Metadata::Get(const string& key, RIDList& results) {
	int size = (int)sizeof(RecordID);
	void* records = tcbdbget(this->database, key.c_str(), key.size(), &size);
	
	if(records != NULL) {
		size_t count = size / sizeof(RecordID);
		results.insert(results.end(), (RecordID*)records, (RecordID*)records + count);
		free(records);
		return true;
	} else {
		return false;
	}
}

bool Retsu::Metadata::Put(const string& key, const string& value) {
	return tcbdbput(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool Retsu::Metadata::PutDup(const string& key, const string& value) {
	return tcbdbputdup(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool Retsu::Metadata::PutDup(const string& key, const RecordID& value) {
  return tcbdbputdup(this->database, key.c_str(), key.size(), &value, sizeof(RecordID));
}

bool Retsu::Metadata::PutCat(const string& key, const RecordID& value) {
	return tcbdbputcat(this->database, key.c_str(), key.size(), &value, sizeof(RecordID));
}

bool Retsu::Metadata::Add(const string& key, const int value, int& result) {
	result = tcbdbaddint(this->database, key.c_str(), key.length(), value);
	
	if(isnan(result)) {
		return false;
	} else {
		return true;
	}
}

bool Retsu::Metadata::Add(const string& key, const double value, double& result) {
	result = tcbdbadddouble(this->database, key.c_str(), key.length(), value);
	
	if(isnan(result)) {
		return false;
	} else {
		return true;
	}
}

/*
 * Returns the last error to occur on the database
 */
std::string Retsu::Metadata::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}

int Retsu::Metadata::ErrorCode() {
	return tcbdbecode(this->database);
}