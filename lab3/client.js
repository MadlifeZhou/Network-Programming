// // 打开一个WebSocket:
// var ws = new WebSocket('ws://localhost:3000');
//
// let was={
//     re:1,
//     fun(){
//         console.log(this)
//     }
// }
//
// //open event
// ws.onopen = function() {
//     console.log("open websocket...");
// };
//
// //close event
// ws.onclose = function() {
//     console.log("close websocket...");
// };
//
// // 响应onmessage事件:
// ws.onmessage = function(msg) {
//     //这里可以处理接收到服务器的数据
//     console.log()
//     console.log(`receive from server:${msg}`);
//     let content = msg.data;
//     console.log(content.username)
// };
//
// function ws_send(){
//     let username = document.getElementById('username').value;
//     let content = document.getElementById('comment_text').value;
//     if (username.toString().length>10){
//         alert("Sorry, the length of your username is too long");
//     }
//     if (content.toString().length>100){
//         alert("Sorry, the length of your comment is too long");
//     }
//     let comment = {"username":username,"content":content,"rest":1};
//     let json_comment = JSON.stringify(comment);
//     // 把这个对象输出
//     console.log(json_comment);
//     // 给服务器发送一个数字
//     ws.send(json_comment);
// }

let em = new Vue({
    el:"#comment",
    data:{
        content2:[
            {"username":"zhou","comment":"ITMO is a good University. It`s always my dream to study in ITMO"},
            {"username":"zhou2","comment":"HDU is a good University. It`s always my dream to study in HDU"}
        ],
        // 存放实验数据
        content:[]
    },
    methods:{
        click(){
            console.log("")
        }
    },
    mounted() {
        axios.get("http://localhost:3000").then(response=>{
            this.content = response.data;
            console.log(this.content)
        });
    }
});


let em2 = new Vue({
    el:"#form",
    data: {
        requestUrl:"http://localhost:3000/data",
        username:"",
        comment:""
    },
    methods:{
        send(){
            if (this.username.length === 0 || this.comment.length === 0){
                alert("Sorry.Your Input text is empty")
                return 0;
            }
            let config = {
                headers: {
                    'Access-Control-Allow-Origin': "*"
                }
            };

            let formData = new FormData();

            //下面是表单绑定的data 数据
            formData.append('username', this.username);
            formData.append('comment', this.comment);
            console.log(formData)
            axios.post("http://localhost:3000/",formData).then((req,resp)=>{
                console.log(resp)
            });
        }
    }


});


