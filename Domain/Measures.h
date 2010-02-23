/*
 *  Measures.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DOMAIN_MEASURES_H_
#define _RETSU_DOMAIN_MEASURES_H_

#include <Common.h>
#include <Domain/Data/Measure.h>

namespace Retsu {
	namespace Domain {
    using namespace std;

		class Measures {
		protected:
			string path;
      
		public:		
			Measures(const string& path);
			
			virtual bool insert(const Data::Record& record);
//			virtual void Lookup(const string& measure, const Data::RIDList& records, vector<double>& results);
		};
	}
}

#endif