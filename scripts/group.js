try {
  results = tables.playback.aggregate({
    'aggregates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
      'average_playtime': function(group) {
        var playtime = 0;
        group.each(function(record) {
          playtime += record['position_to'] - record['position_from']
        })
        return playtime / 60;
      }
    },
  
    'group': ['item_id', 'show_id'],
    
    'sample_size': 500
  });

  print(results);
  
  if(results.length > 0) {
    for(var i = 0; i < results.length; i++) {
      print(results[i]['count']);
      print(results[i]['total']);
      print(results[i]['average']);
    }
  } else {
    print("No results!");
  }
} catch(err) {
  print("An error occurred");
  print(err);
}