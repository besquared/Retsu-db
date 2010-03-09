var shows = ["Learn Japanese Podcast", "Nocturnal Sunshine", "Nocturnal"];
var episodes = ["00000001", "00000002", "00000003", "00000004"];

var playback = tables.playback;
for(var i = 0; i < 10; i++) {
  var show_idx = Math.floor(Math.random() * shows.length);
  var episode_idx = Math.floor(Math.random() * episodes.length);
  playback.insert({'show_id': shows[show_idx], 'episode_id': episodes[episode_idx]});
}

tables.playback.aggregate({'group': ['item_id', 'show_id']});