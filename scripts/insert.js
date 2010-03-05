print(tables.playback);

var playback = tables.playback;
for(var i = 0; i < 100000; i++) {
  playback.insert({'mykey': 'another thing'});
}