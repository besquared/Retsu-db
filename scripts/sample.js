try {
  results = tables.playback.aggregate({  
    'group': ['show_id', 'episode_id'],
    'aggregates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
    }, 'conditions': {
      'amount': {'gt': 100},
      'amount': {'lt': 200},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'sample_size': 10
  });
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}