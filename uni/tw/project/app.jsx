const express = require("express");

express().use(express.static("./static")).listen(9393, console.log("App listening on port: 9393"));