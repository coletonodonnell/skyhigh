const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const cors = require('cors')
const port = 3000

var fs = require('fs');

app.use( bodyParser.json() );
app.use(bodyParser.urlencoded({
    extended: true}));
app.use(cors())

app.use(bodyParser.urlencoded({
    extended: true})); 
app.use(cors())
app.use(express.static(__dirname))

app.post('/upload', (req, res) => {
    // console.log(req.body.org)
    // console.log(req.body.dest)
    // console.log(req.body.status)

    var off_on;
    if (req.body.status) {
        off_on = 1;
    } else {
        off_on = 0;
    }


    fs.writeFile('selection.out', req.body.org + "\n" + req.body.dest + "\n" + off_on, function(err) {
        if (err) throw err;
    });

    res.redirect('..')
    res.end()
})

app.get('/', (req, res)=>{
    res.sendFile("index.html")
})

//Start your server on a specified port
app.listen(port, ()=>{
    console.log(`Server is running on port ${port}`)
})