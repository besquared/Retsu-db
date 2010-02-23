#include <Common.h>
#include <Domain/Base.h>

using namespace Retsu;

int main (int argc, char * const argv[]) {
  Domain::Base domain("playback", ".");
  
  Domain::Data::Record record(1);
  record.insert("duration", 10.50);
  record.insert("action", "played");
  record.insert("user_id", "00000001");
  record.insert("session_id", "00000001");
  
  for(size_t i = 0; i < 1000; i++) {
    domain.insert(record);
  }
  
  return 0;
}
