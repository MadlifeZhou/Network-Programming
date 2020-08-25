var express = require('express');
var app = express();
const cors = require("cors")

const port = 3000;

app.use(express.json());
app.use(cors())

let data = [
    {"username": "zhou", "comment": "ITMO is a good University. It`s always my dream to study in ITMO"},
    {"username": "zhou2", "comment": "HDU is a good University. It`s always my dream to study in HDU"}
];

app.post('/', (request, response) => {
    console.log(request.body);
    let item = request.body;
    data.push(item)
    console.log(data);
    response.status(201).send;
});

app.get('/index.html', function (req, res) {
    res.sendFile( __dirname + "/" + "index.html" );
})

app.get('/process_get', function (req, res) {
    // 输出 JSON 格式
    var response = {
        "first_name":req.query.first_name,
        "last_name":req.query.last_name
    };
    console.log(response);
    res.end(JSON.stringify(response));
})

app.get('/', (request, response) => {
    // response.setHeader("Access-Control-Allow-Origin", "*");
    response.send(data);
});

var server = app.listen(3000, function () {
    var port = server.address().port
    console.log(`Visit the index page: http://localhost:${port}/index.html`)
})