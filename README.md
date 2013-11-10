WSChat
======

Chat program for different programming language over Websocket

Group Member: Wenxuan Zhao, Yonghong Chen, Guangle Shi

Protocol
--------
```
nick::<NickName>
text::<Broadcast Message>
text:<Target NickName>:<Private Message>
bin::<Broadcast Message>
bin:<Target NickName>:<Private Message>

nick:success
nick:fail

text:<Source Nickname>:<Message>
bin:<Source Nickname>:<Message>
```
