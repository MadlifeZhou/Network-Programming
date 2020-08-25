// // 导入WebSocket模块:
// const WebSocket = require('ws');
//
// // 实例化:
// const wss = new WebSocket.Server({
//     //端口号
//     port: 3000
// });
//
// console.log("setup server...");
//
// wss.on('connection', function (ws) {
//     console.log(`[SERVER] connection()`);
//     ws.on('message', function (message) {
//         let json_message = JSON.parse(message);
//         console.log(json_message.username)
//         console.log(`[SERVER] Received: ${message}`);
//         let message_string = JSON.stringify(json_message);
//         ws.send(message_string, (err) => {
//             if (err) {
//                 console.log(`[SERVER] error: ${err}`);
//             }
//         });
//     })
// });

const express = require('express')
const app = express();
const port = 3000;

let data = [
    {"username":"zhou","comment":"ITMO is a good University. It`s always my dream to study in ITMO"},
    {"username":"zhou2","comment":"HDU is a good University. It`s always my dream to study in HDU"}
]

app.get('/data',(request,response)=>{
    response.send(data);
});

app.get('/',(request,response)=>{
   data.push(request.data)
   response.send(data);
});

app.listen(port,(err)=>{
   if (err){
       return console.log('something bad happened',err)
   }
   console.log(`server is listening on ${port}`)
});





