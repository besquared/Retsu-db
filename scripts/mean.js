try {
  results = tables.playback.mean('amount', {
    'sample': 10000, 'confidence': 99.0,
    // 'bootstrap': {'replicate': 1000, 'interval': 'basic'},
    'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'group': ['show_id', 'episode_id']
  })
  
  // bootstrap intervals are basic, percentile, bca 
  //  and studentized with basic being the default
  
  // [
  //  {'show_id': 1, ..., 'estimate': 28.9, 'interval': [24.6, 38.8], 'variance': 9.65, ...},
  //  {'show_id': 2, ..., 'estimate': 27.6, 'interval': [23.5, 34.6], 'variance': 8.86, ...},
  // ]
  
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}