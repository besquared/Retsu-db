tables.playback.aggregate(
  'where' : {}
  'group': ['item_id', 'show_id'],
  'total_amt': {'sum': 'amount'},
  'average_amt': function(group) {
    group.sum('amount') / group.count();
  }
);