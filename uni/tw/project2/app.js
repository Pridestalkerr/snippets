//const mysql = require('mysql');
const express = require("express");
//const session = require('express-session');
const bodyParser = require('body-parser');
const path = require("path");
const sqlite = require("sqlite3")

let db = new sqlite.Database("./db/main.db", sqlite.OPEN_READWRITE);

let app = express();
app.use(express.static(path.join(__dirname + "/static/")));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));

app.get("/messages", function(request, response){
	db.all("select * from messages order by id desc limit 20", [], (error, results) => {
		response.send(results.reverse());
	});
});

app.post("/messages", function(request, response){
	//redirect to index
	console.log(request.body);

	db.run("insert into messages VALUES(NULL, ?, ?, datetime('now'))", [request.body.username, request.body.message], function(error, results){
		if(error)
			console.log(error);
		else
		{
			db.each("select date from messages where id = ?", ['' + this.lastID], (error, results) => {
				let em = JSON.parse(JSON.stringify(request.body));
				em.date = results.date;
				//console.log(em);
				io.emit("message", em);
			});
		}

	});

	response.sendStatus(200);

});


let sv = app.listen(3000);



const io = require("socket.io")(sv);

io.on("connection", () => {
	console.log("user connected");
});
