try {
  results = tables.playback.aggregate({  
    'group': ['item_id', 'show_id'],
    'aggregates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
    }, 'conditions': {
      'episode_id': {'eq': '00000001'}
    }, 'sample_size': 1000
  });
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}