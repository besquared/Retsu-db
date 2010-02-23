/*
 *  Base.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DOMAIN_BASE_H
#define _RETSU_DOMAIN_BASE_H

#include <Common.h>
#include <Domain/Measures.h>
#include <Domain/Dimensions.h>

namespace Retsu {
	namespace Domain {
    using namespace std;

		class Base {
		protected:
			string path;
			string dpath;
			
		public:
      Domain::Measures* measures;
			Domain::Dimensions* dimensions;
			
			Base(const string& path, const string& dpath);
			virtual ~Base();
      
      void insert(const Data::Record& record);
		};
	}
}

#endif