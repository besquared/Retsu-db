try {
  results = tables.playback.estimate({
    'estimates': {
      'total': {'sum': 'amount'},
      'count': {'count': true},
      'average': {
        'mean' : 'amount', 'confidence': 99.0, 
        // '
        // 'bootstrap': {'replicate': 1000, 'interval': 'basic'},
        // 'variance': true, 'stderr': true, 'skew': false, 'kurtosis': false
      }
    }, 'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'group': ['show_id', 'episode_id'],
    'sample': 10000
  });
  
  // bootstrap methods are basic, percentile, bca 
  //  and studentized with basic being the default
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}