const express = require('express')
const bodyParser = require('body-parser');
const app = express();
const querystring = require('querystring');
const port = 3000;

// 创建 application/x-www-form-urlencoded 编码解析
let urlencodedParser = bodyParser.urlencoded({extended: false})

app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "X-Requested-With");
    res.header("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");
    res.header("X-Powered-By",' 3.2.1')
    res.header("Content-Type", "application/json;charset=utf-8");
    next();
});

let data = [
    {"username": "zhou", "comment": "ITMO is a good University. It`s always my dream to study in ITMO"},
    {"username": "zhou2", "comment": "HDU is a good University. It`s always my dream to study in HDU"}
]

app.post('/', (request, response) => {

    console.log(request.body)
    response.end("hello")
    response.send(data)
});

app.get('/', (request, response) => {
    response.setHeader("Access-Control-Allow-Origin", "*");
    response.send(data);
});

app.listen(port, (err) => {
    if (err) {
        return console.log('something bad happened', err)
    }
    console.log(`server is listening on ${port}`)
});





