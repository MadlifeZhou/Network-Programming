// 打开一个WebSocket:
var ws = new WebSocket('ws://localhost:3000');

let was={
    re:1,
    fun(){
        console.log(this)
    }
}

//open event
ws.onopen = function() {
    console.log("open websocket...");
};

//close event
ws.onclose = function() {
    console.log("close websocket...");
};

// 响应onmessage事件:
ws.onmessage = function(msg) {
    //这里可以处理接收到服务器的数据
    console.log()
    console.log(`receive from server:${msg}`);
    let content = msg.data;
    console.log(content.username)
};

function ws_send(){
    let username = document.getElementById('username').value;
    let content = document.getElementById('comment_text').value;
    if (username.toString().length>10){
        alert("Sorry, the length of your username is too long");
    }
    if (content.toString().length>100){
        alert("Sorry, the length of your comment is too long");
    }
    let comment = {"username":username,"content":content,"rest":1};
    let json_comment = JSON.stringify(comment);
    // 把这个对象输出
    console.log(json_comment);
    // 给服务器发送一个数字
    ws.send(json_comment);
}