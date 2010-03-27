try {
  results = tables.playback.aggregate({
    'aggregates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
    }, 'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'group': ['show_id', 'episode_id'], 'sample_size': 10000
  });
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}