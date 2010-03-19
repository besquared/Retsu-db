var shows = ["Learn Japanese Podcast", "Nocturnal Sunshine", "Nocturnal"];
var episodes = ["00000001", "00000002", "00000003", "00000004"];

var playback = tables.playback;
for(var i = 0; i < 100000; i++) {
  var amount = Math.random() * 1000;
  var show_idx = Math.floor(Math.random() * shows.length);
  var episode_idx = Math.floor(Math.random() * episodes.length);
  playback.insert({'amount': amount, 'show_id': shows[show_idx], 'episode_id': episodes[episode_idx]});
}
