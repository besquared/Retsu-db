try {
  tables.playback.mean('amount', {
    'sample': 10000, 'confidence': 99.0,
    // 'bootstrap': {'replicate': 1000, 'interval': 'basic'},
    // 'variance': true, 'stderr': true, 'skew': false, 'kurtosis': false
    'conditions': {
      'amount': {'lt': 500, 'gt': 100},
      'show_id': {'eq': 'Nocturnal Sunshine'}
    }, 'group': ['show_id', 'episode_id']
  })
  
  // {'estimate': 28.9, 'interval': [24.6, 38.8], 'variance': 10.86, ...}
  
  // results = tables.playback.estimate({
  //   'estimates': {
  //     'purchase_amount': {
  //       'mean' : 'amount', 'confidence': 99.0,
  //     }
  //   }, 'conditions': {
  //     'amount': {'lt': 500, 'gt': 100},
  //     'show_id': {'eq': 'Nocturnal Sunshine'}
  //   }, 'group': ['show_id', 'episode_id'],
  //   'sample': 10000
  // });
  
  // bootstrap methods are normal, percentile, bca 
  //  and studentized with normal being the default
  
  // example return
  // {..., 'average': {'estimate': 28.9, 'interval': [24.6, 38.8], 'variance': 10.86, ...}}
  inspect(results);
} catch(err) {
  print("An error occurred");
  print(err);
}