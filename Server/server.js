#!/usr/bin/env node
var http = require("http");
var WebSocketServer = require("websocket").server;

/* Default Port */
var PORT = 8999;

/* Create HTTP Server & Implementation */
var server = http.createServer(function(request, response) {
  response.writeHead(501);
  response.end();
}).listen(PORT, function() {
  console.log("WSChat Server is listening on port " + PORT);
});

/* Create Websocket Server */
wsServer = new WebSocketServer({httpServer: server});

/* Websocket Server Implementation */
var WSChat = {};
WSChat.connections = [];
WSChat.checkNotLogin = function (conn) {
  if (!conn.nickName) {
    conn.sendUTF("error:Not login!");
    return true;
  }

  return false;
}
WSChat.checkEmptyMessage = function (conn, message) {
  if (message)
    return false;

  conn.sendUTF("error:Empty message!");
  return true;
}
WSChat.doSend = function (conn, dest, message) {
  if (WSChat.checkNotLogin(conn) || WSChat.checkEmptyMessage(conn, message))
    return;

  var found = false;
  for (var c in WSChat.connections) {
    if (WSChat.connections[c].nickName == dest) {
      WSChat.connections[c].sendUTF("pmsg:" + conn.nickName + ":" + message);
      found = true;
      break;
    }
  }

  if (found) {
    conn.sendUTF("to:success");
  } else {
    conn.sendUTF("to:failed:User not exist!");
  }
}
WSChat.doBroadCast = function (message, includeNotLogin) {
  for (var c in WSChat.connections) {
    if (WSChat.connections[c].nickName || includeNotLogin)
      WSChat.connections[c].sendUTF(message);
  }
}
WSChat.doBroadCastMsg = function (conn, message) {
  if (WSChat.checkNotLogin(conn) || WSChat.checkEmptyMessage(conn, message))
    return;
  WSChat.doBroadCast("msg:" + conn.nickName + ":" + message, false);
}
WSChat.cmdList = function (conn) {
  var list = "";
  for (var i in WSChat.connections) {
    if (WSChat.connections[i].nickName)
      list += WSChat.connections[i].nickName + ":";
  }
  conn.sendUTF("list:" + list);
}
WSChat.cmdNick = function (conn, nick) {
  if (nick) {
    if (nick.match(/^[_A-Za-z0-9]+$/)) {
      // check duplicate
      var alreadyExist = false;
      for (var i in WSChat.connections) {
        if (WSChat.connections[i].nickName == nick) {
          alreadyExist = true;
          break;
        }
      }

      if (alreadyExist) {
        conn.sendUTF("nick:fail:Nickname \"" + nick + "\" " 
          + "is already in use!")
      } else {
        conn.nickName = nick;
        conn.sendUTF("nick:success");
        WSChat.doBroadCast("login:" + nick, true);
      }
    } else {
      conn.sendUTF("nick:fail:Illegal character \""
        + nick.charAt(nick.match(/[^_A-Za-z0-9]/).index)
        + "\" found in nickname \"" + nick + "\"!");
    }
  } else
    conn.sendUTF("nick:fail:Empty nickname!");
}
WSChat.processCommand = function (conn, cmd, params) {
  switch (cmd.trim()) {
    case "list":
      WSChat.cmdList(conn);
      break;

    case "nick":
      WSChat.cmdNick(conn, params.trim());
      break;
      
    case "to":
      var dest = params;
      var message = "";

      var pos = params.indexOf(' ');
      if (pos != -1) {
        dest = params.substring(0, pos);
        message = params.substring(pos + 1);
      }

      WSChat.doSend(conn, dest, message);
      break;
      
    default:
      // escape
      if (cmd.charAt(0) == '/') {
        WSChat.doBroadCastMsg(conn, cmd + params == "" ? "" : ' ' + params);
        break;
      }
      conn.sendUTF("error:Command \"" + cmd + "\" not found!");
  }
}
WSChat.processTextMessage = function (conn, message) {
  if (message.charAt(0) == '/') {
    // command mode, parse cmd and param
    message = message;
    var cmd = message;
    var params = "";

    var pos = message.indexOf(' ');
    if (pos != -1) {
      cmd = message.substring(0, pos);
      params = message.substring(pos + 1);
    }
    cmd = cmd.substring(1); // remove '/'

    WSChat.processCommand(conn, cmd, params);
  } else
    WSChat.doBroadCastMsg(conn, message);
}
WSChat.processBinaryMessage = function (conn, message) {
  console.log("FIXME: Received Binary Message of "
    + message.binaryData.length + " bytes");
}
WSChat.handleMessage = function (conn, message) {
  switch (message.type) {
    case "utf8":
      WSChat.processTextMessage(conn, message.utf8Data);
      break;

    case "binary":
      WSChat.processBinaryMessage(conn, message);
      break;

    default:
      console.log("FIXME: Unexpected error type: " + message.type);
  }
}
WSChat.handleClose = function (conn) {
  if (conn.nickName)
    WSChat.doBroadCast("logout:" + conn.nickName, true);
  delete WSChat.connections[WSChat.connections.indexOf(conn)];
}

/* Hook Websocket Server */
wsServer.on("request", function (request) {
  var conn = request.accept(null, request.origin);
  conn.nickName = null;

  conn.on("message", function (message) {
    WSChat.handleMessage(conn, message);
  });
  conn.on("close", function (reasonCode, description) {
    WSChat.handleClose(conn);
  });

  WSChat.connections.push(conn);
});
