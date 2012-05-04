alert('Nice melons!');
var msgRec = gameComms.getGameJson();
alert(msgRec);
var msgSend = 'Melons from WebComms';
gameComms.setGameJson(msgSend);
