const char *HTML_CONTENT = R"=====(
    <!doctype html>
    <html lang="en">
        <head>
            <meta charset="UTF-8" />
            <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, maximum-scale=1, minimum-scale=1" />
            <title>ESP BOT Controller</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    margin: 0;
                    padding: 20px;
                    display: flex;
                    flex-direction: column;
                    align-items: center;
                    background-color: white;
                }
                h1 {
                    font-size: 24px;
                    margin-bottom: 5px;
                }
                h2 {
                    font-size: 20px;
                    margin-top: 0;
                    margin-bottom: 20px;
                }
                .button-group {
                    display: grid;
                    grid-template-columns: 1fr 1fr;
                    gap: 10px;
                    margin-bottom: 30px;
                }
                .button {
                    padding: 10px 20px;
                    font-size: 16px;
                    border: none;
                    border-radius: 5px;
                    background-color: #90ee90;
                    color: black;
                }
                .arrow-buttons {
                    display: grid;
                    grid-template-columns: repeat(3, 1fr);
                    gap: 10px;
                }
                .arrow-button {
                    width: 60px;
                    height: 60px;
                    border-radius: 50%;
                    border: none;
                    background-color: #e6e6fa;
                    font-size: 24px;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                }
                .arrow-button:nth-child(1) {
                    grid-column: 2;
                }
                .arrow-button:nth-child(2) {
                    grid-column: 1;
                    grid-row: 2;
                }
                .arrow-button:nth-child(3) {
                    grid-column: 3;
                    grid-row: 2;
                }
                .arrow-button:nth-child(4) {
                    grid-column: 2;
                    grid-row: 3;
                }
            </style>

            <script>
                var CMD_PICK = 0;
                var CMD_RELEASE = 1;
                var CMD_UP = 2;
                var CMD_DOWN = 3;

                var CMD_FROWARD = 4;
                var CMD_BACKWARD = 5;
                var CMD_LEFT = 6;
                var CMD_RIGHT = 7;

                var CMD_STOP = 10;

                var ws = null;

                function init() {
                    if (ws == null) {
                        ws = new WebSocket("ws://" + window.location.host + ":81");
                    }

                    var container = document.querySelector("#container");
                    container.addEventListener("touchstart", mouse_down);
                    container.addEventListener("touchend", mouse_up);
                    container.addEventListener("touchcancel", mouse_up);
                    container.addEventListener("mousedown", mouse_down);
                    container.addEventListener("mouseup", mouse_up);
                    container.addEventListener("mouseout", mouse_up);

                    const buttons = document.querySelectorAll(
                        ".button-group .button",
                    );
                    buttons.forEach((button) => {
                        button.addEventListener("click", handleButtonClick);
                    });
                }

                function handleButtonClick(event) {
                    const id = event.target.id;
                    send_command(id);
                }

                function mouse_down(event) {
                    if (event.target !== event.currentTarget) {
                        var id = event.target.id;
                        send_command(id);
                    }
                    event.stopPropagation();
                    event.preventDefault();
                }

                function mouse_up(event) {
                    if (event.target !== event.currentTarget) {
                        var id = event.target.id;
                        send_command(CMD_STOP);
                    }
                    event.stopPropagation();
                    event.preventDefault();
                }

                function send_command(cmd) {
                    if (ws != null) if (ws.readyState == 1) ws.send(cmd + "\r\n");
                }

                window.onload = init;
            </script>
        </head>
        <body>
            <h1>ESP BOT</h1>
            <h2>Controller</h2>

            <div class="button-group">
                <button class="button" id="0">PICK</button>
                <button class="button" id="1">REL</button>
                <button class="button" id="2">UP</button>
                <button class="button" id="3">DOW</button>
            </div>

            <div class="arrow-buttons" id="container">
                <button class="arrow-button" id="4">&#8593;</button>
                <button class="arrow-button" id="5">&#8592;</button>
                <button class="arrow-button" id="6">&#8594;</button>
                <button class="arrow-button" id="7">&#8595;</button>
            </div>
        </body>
    </html>
)=====";
