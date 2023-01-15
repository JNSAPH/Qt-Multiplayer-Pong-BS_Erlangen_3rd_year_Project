// Connect to websocket on localhost:1214
let playerdata = {
    "PlayerNumber": new Number(),
    "UUID": new String(),
}

let ws;

let gameState = new Object();

function connect() {
    ws = new WebSocket("ws://localhost:1214");
    ws.onopen = function() {
        console.log("Connected to websocket");
    };
    ws.onmessage = function(evt) {
        onWSMessage(evt);
    };
    ws.onclose = function() {
        console.log("Disconnected from websocket");
        // reload page
        location.reload();
    };
}

function onWSMessage(evt) {
    let parsed = JSON.parse(evt.data);
    switch (parsed.code) {
        case 200:
            // Player Joined
            playerdata.PlayerNumber = parsed.PlayerNumber;
            playerdata.UUID = parsed.UUID;
            document.getElementById("wsDebugLogPlayeState").innerHTML = JSON.stringify(playerdata);
            break;
        case 201:
            // Game is starting
            break;
        case 203:
            // Player Left
            break;
        case 204:
            // Game state update
            gameState = parsed;
            document.getElementById("wsDebugLogBall").innerHTML = JSON.stringify(gameState.ball);
            document.getElementById("wsDebugLogPaddleL").innerHTML = JSON.stringify(gameState.paddle1);
            document.getElementById("wsDebugLogPaddleR").innerHTML = JSON.stringify(gameState.paddle2);
            document.getElementById("wsDebugLogScore").innerHTML = JSON.stringify(gameState.score1) + " - " + JSON.stringify(gameState.score2);; 

            document.getElementById("paddleLeft").style.top = gameState.paddle1.y + "px";
            document.getElementById("paddleRight").style.top = gameState.paddle2.y + "px";
            document.getElementById("ball").style.top = gameState.ball.y + "px";
            document.getElementById("ball").style.left = gameState.ball.x + "px";
            
            break;
        default:
            break;
    }
}

// Button onclicks
btnMoveUp.onclick = function() {
    sendWSACtion("up");
}

btnMoveDown.onclick = function() {
    sendWSACtion("down");
}

// Send a message to the websocket
function sendWSACtion(action) {
    let message = JSON.stringify({
        "code": 110,
        "player": playerdata.PlayerNumber,
        "action": action,
    });
    console.log(message);
    ws.send(message);
}


// run connect on page load
window.onload = connect;