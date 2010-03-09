var playback = tables.playback;
for(var i = 0; i < 10; i++) {
  playback.insert({'item_id': '00000001', 'show_id': '00000001'});
}

tables.playback.aggregate({
  'group': ['item_id', 'show_id']
});