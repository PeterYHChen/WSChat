WSChat
======

Chat program for different programming language over Websocket

Group Member: Wenxuan Zhao, Yonghong Chen, Guangle Shi

Protocol
--------

Register a nickname (success):
```
--> /nick <nickname>
<-- nick:success
<-! nick:failed:<reason>
```
Note: nick name only allow charset [_A-Za-z0-9]


List current users:
```
--> /list
<-- list:<nickname1>:<nickname2>:...:
```

Boardcast message:
```
--> <message>
```

Send message:
```
--> /to <nickname> <message>
<-! to:failed:<reason>
```
