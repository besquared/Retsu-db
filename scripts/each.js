print("does print work");

var records = [];
tables.playback.each(
  function(record) {
    // print("inside each!");
    records.push(record.id);
  }
)

// print(records);