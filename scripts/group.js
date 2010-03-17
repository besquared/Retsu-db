var shows = ["Learn Japanese Podcast", "Nocturnal Sunshine", "Nocturnal"];
var episodes = ["00000001", "00000002", "00000003", "00000004"];

var playback = tables.playback;
for(var i = 0; i < 100000; i++) {
  var amount = Math.random() * 1000;
  var show_idx = Math.floor(Math.random() * shows.length);
  var episode_idx = Math.floor(Math.random() * episodes.length);
  playback.insert({'amount': amount, 'show_id': shows[show_idx], 'episode_id': episodes[episode_idx]});
}

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
  
    'conditions': {'occurred_at': {'gt': 147000000}}
  });

  print(results);

  print(results[0]['count']);
  print(results[0]['total']);
  print(results[0]['average']);
  print(results[1]['count']);
  print(results[1]['total']);
  print(results[1]['average']);
  print(results[2]['count']);
  print(results[2]['total']);
  print(results[2]['average']);
} catch(err) {
  print("An error occurred");
  print(err);
}