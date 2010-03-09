var shows = ["Learn Japanese Podcast", "Nocturnal Sunshine", "Nocturnal"];
var episodes = ["00000001", "00000002", "00000003", "00000004"];

var playback = tables.playback;
for(var i = 0; i < 10; i++) {
  var show_idx = Math.floor(Math.random() * shows.length);
  var episode_idx = Math.floor(Math.random() * episodes.length);
  playback.insert({'show_id': shows[show_idx], 'episode_id': episodes[episode_idx]});
}

tables.playback.aggregate({
  'aggregates': {
    'total': {'sum': 'amount'},
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