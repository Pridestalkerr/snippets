const express = require("express");

express().use(express.static("./static")).get("/", function(request, response){
	response.send("Hello World!");
}).listen(8080, console.log("App listening on port: 8080"));