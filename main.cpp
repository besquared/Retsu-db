#include <Common.h>
#include <Domain/Base.h>

using namespace Retsu;

int main (int argc, char * const argv[]) {
//  Domain::Base domain("playback", ".");
//  
//  std::vector<Domain::Data::Record> records;
//  
//  for(size_t i = 0; i < 100000; i++) {
    Domain::Data::Record record(1.0);
    record.insert("duration", 10.50);
//    record.insert("action", "played");
//    record.insert("user_id", "00000001");
//    record.insert("session_id", "00000001");
//    records.push_back(record);
//  }
//  
//  
//  boost::timer t;
//  
//  for(size_t j = 0; j < records.size(); j++) {
//    domain.insert(records[j]);
//    std::cout << records[j].id << std::endl;
//  }
//  
//  std::cout << "Completed in " << t.elapsed() << " seconds." << std::endl;
  
  return 0;
}
