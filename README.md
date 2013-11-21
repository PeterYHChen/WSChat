WSChat
======

Chat program for different programming language over Websocket

Group Member: Wenxuan Zhao, Yonghong Chen, Guangle Shi

Protocol
--------

List current users (everyone can send):
```
--> /list
<-- list:<nickname1>:<nickname2>:...:
```

Register a nickname (success):
```
--> /nick <nickname>
<-- nick:success
<-! nick:failed:<reason>
```

Boardcast message (require nickname is registered):
```
--> <message>
```

Receive broadcast event (everyone has a nickname will receive):
```
<-- msg:<sender>:<message>
```

Send private message (require nickname is registered):
```
--> /to <nickname> <message>
<-- to:success
<-! to:failed:<reason>
```

Receive private message event (both sender and receiver will receive):
```
<-- pmsg:<sender>:<message>
```

Login event (everyone connected will receive):
```
<-- login:<nickname>
```

Logout event (everyone connected will receive):
```
<-- logout:<nickname>
```

General error event (sender will receive):
```
<-! error:<error information>
```

Note
----

* Nickname only allow charset ```[_A-Za-z0-9]```
* Message won't include the tailing ```\n```