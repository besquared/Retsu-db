/*
 *  Dimensions.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DOMAIN_DIMENSIONS_H_
#define _RETSU_DOMAIN_DIMENSIONS_H_

#include <Common.h>
#include <Domain/Data/Dimension.h>
#include <Domain/Data/Record.h>

namespace Retsu {
	namespace Domain {
    using namespace std;

		class Dimensions {
		protected:
			string path;
			
		public:
			Dimensions(const string& path);
			
			virtual bool insert(const Data::Record& record);
//			virtual void Lookup(const string& dimension, const Data::RIDList& records, vector<string>& results);
		};
	}
}

#endif