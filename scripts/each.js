var sum = 0;
var records = [];
tables.playback.each(
  function(record) {
    sum += record.id;
    record.mykey;
    // print("inside each!");
    // print(record.mykey);
  }
)

print(sum);