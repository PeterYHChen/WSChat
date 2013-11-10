WSChat
======

Chat program for different programming language over Websocket

Group Member: Wenxuan Zhao, Yonghong Chen, Guangle Shi

Protocol
--------

Register a nick name (success):
```
--> /nick <nickname>
<-- success
```

Register a nick name (failed):
```
--> /nick <nickname>
<-- failed:<reason>
```

Note: nick name only allow charset [_A-Za-z0-9]
