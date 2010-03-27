try {
  results = tables.playback.aggregate({  
    'group': ['show_id', 'episode_id'],
    'aggregates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
    }, 'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'sample_size': 2000
  });
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}