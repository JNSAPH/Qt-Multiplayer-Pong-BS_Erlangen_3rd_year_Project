// Connect to websocket on localhost:1214
let playerdata = {
    "PlayerNumber": new Number(),
    "UUID": new String(),
}

let csvArray = new Array();

function handleFileSelect(evt) {
    let files = evt.target.files; // FileList object

    // use the 1st file from the list
    let f = files[0];

    let reader = new FileReader();

    // print file contents to console
    reader.onload = function (e) {
        // parse csv
        let csv = e.target.result;
        let allTextLines = csv.split(/\r,\n/);
        let headers = allTextLines[0].split(',');
        let lines = [];

        for (let i = 1; i < allTextLines.length; i++) {
            let data = allTextLines[i].split(',');
            if (data.length == headers.length) {
                let tarr = [];
                for (let j = 0; j < headers.length; j++) {
                    tarr.push(data[j]);
                }
                lines.push(tarr);
            }
        }
    }


    reader.readAsText(f);



    /*
        csvArray.pushs({
            "paddle1_x": new Number(),
            "paddle1_y": new Number(),
            "paddle2_x": new Number(),
            "paddle2_y": new Number(),
            "ball_x": new Number(),
            "ball_y": new Number(),
            "ball_vx": new Number(),
            "ball_vy": new Number(),
            "score1": new Number(),
            "score2": new Number(),
            "timestamp": new Number(),
        })
        */
}

/*
CSV format:
"paddle1_x", "paddle1_y", "paddle2_x", "paddle2_y", "ball_x", "ball_y", "ball_vx", "ball_vy", "score1", "score2", "timestamp"
29,230,625,230,331.5,261.349,0.5,0.348697,0,0,1676023096642

*/

// Event listener for file upload
document.getElementById('upload').addEventListener('change', handleFileSelect, false);

// run connect on page load
window.onload = connect;
