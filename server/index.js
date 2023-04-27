const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const cors = require('cors')
const port = 3000

var fs = require('fs');

// Guided by: https://dev.to/gbudjeakp/how-to-connect-your-client-side-to-your-server-side-using-node-and-express-2i71
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true}));
app.use(cors())

app.use(bodyParser.urlencoded({
    extended: true})); 
app.use(cors())
app.use(express.static(__dirname))

function sleep (time) {
    return new Promise((resolve) => setTimeout(resolve, time));
}

// API for file write
app.post('/upload', (req, res) => {
    var off_on;
    if (req.body.status) {
        off_on = 1;
    } else {
        off_on = 0;
    }

    fs.writeFile('selection.out', req.body.org + "\n" + req.body.dest + "\n" + off_on, function(err) {
        if (err) throw err;
    });

    sleep(25000).then(() => {
        res.redirect('..')
        res.end()
    })
})

app.get('/', (req, res)=>{
    res.sendFile("index.html")
})

app.listen(port, ()=>{
    console.log(`Server is running on port: ${port}`)
})