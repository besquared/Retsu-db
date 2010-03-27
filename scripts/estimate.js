try {
  results = tables.playback.estimate({
    'estimates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {'average' : 'amount'},
    }, 'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'group': ['show_id', 'episode_id'],
    'sample': 10000, 'confidence': 97.5, 'method': 'normal'
  });

  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}