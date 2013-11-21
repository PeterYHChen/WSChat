function output(text) {
	var msgblock = $("<div>").text(text);
	$("#message-board").append(msgblock);
}

var ws;

$(document).ready(function () {
	var parseReason = function (failMsg) {
		var pos = failMsg.indexOf(":");
		if (pos == -1
			|| failMsg.substring(0, failMsg.indexOf(":")) != "failed") {
			return failMsg;
		} else {
			return failMsg.substring(failMsg.indexOf(":") + 1);
		}
	}

	var handlePayload = function (data) {
		var pos = data.indexOf(":");
		if (pos == -1) {
			output("FIXME: Unknown payload: " + data);
			return;
		}

		var protocol = data.substring(0, pos);
		var message = data.substring(pos + 1);

		switch (protocol) {
			case "list":
				if (message == "") {
					output("Nobody is current online");
					return;
				}

				message = message.split(" ").join(", ");
				output("Current online list: " + message);
				return;

			case "nick":
				if (message == "success") {
					output("Set nickname successfully!");
				} else {
					output("Set nick name failed: " + parseReason(message));
				}
				return;

			case "msg":
			case "pmsg":
				var pos = message.indexOf(":");
				if (pos == -1)
					return;
				output((protocol == "pmsg" ? "[Private] " : "") + message.substring(0, pos) + ": "
					+ message.substring(pos + 1));
				return;
				

			default:
				output("FIXME: Unknown protocol: [" + protocol + "] " 
					+ "with message [" + message + "]");
				return;

		}
	}

	ws = new WebSocket("ws://tunnel.vince.im:8999");

	ws.onopen = function () {
		output("[Client has connected]");
	}

	ws.onerror = function () {
		output("[Error when writing to socket, hanging up]");
	}

	ws.onmessage = function (event) {
		handlePayload(event.data);
	}

	ws.onclose = function (event) {
		console.log("[Connection closed by the server]");
	}
});

$("[name=submit]").click(function (argument) {
	// body...
});