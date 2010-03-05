var sum = 0;
var records = [];
tables.playback.each(
  function(record) {
    sum += record.id;
    // print("inside each!");
    // print(record.mykey);
  }
)

print(sum);