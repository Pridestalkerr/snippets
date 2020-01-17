
var username_val;


function post_message(msg)
{
	let xhr = new XMLHttpRequest();
	xhr.open("POST", "/messages", true);
	xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.send(JSON.stringify(msg));
}

let button = document.getElementById("send");

button.onclick = () => {
	post_message({
		username: username_val,
		message: document.getElementById("message").value
	});
	document.getElementById("message").value = '';
};

let set_user_btn = document.getElementById("set_user");

set_user_btn.onclick = () => {
	username_val = document.getElementById("username").value;
	document.getElementById("username").value = '';
	curr_user.innerHTML = username_val;

	//also store it why not
	localStorage.setItem('username_val', username_val);
	localStorage.setItem('username_val_set', 1);
};



function get_messages()
{
	let xhr = new XMLHttpRequest();
	xhr.open("GET", "/messages", false);

	xhr.send(null);

	return xhr.responseText;
}

function make_msg(message)
{
	let container = document.createElement("div");
	//container.appendChild(document.createElement(""))

	container.setAttribute("style", "color:red; border: 1px solid blue;");

	let nm = document.createElement("div");
	nm.onclick = (event) => {
		//window.location.href += message.username;
		event.stopPropagation();
	};

	container.appendChild(nm).innerHTML = message.username + " - " + message.date;


	let ms = document.createElement("div");
	ms.setAttribute("style", "height:40px; overflow: hidden;");
	container.onclick = () => {
		ms.setAttribute("style", "heigh: auto;")
	};

	container.appendChild(ms).innerHTML = message.message;
	return container;
}

function arrange_messages(msg_box, messages)
{
	let arr = JSON.parse(messages);
	for(const msg of arr)
	{
		//console.log(msg);
		msg_box.appendChild(make_msg(msg)).scrollIntoView();
	}
}


//init

arrange_messages(document.getElementById("msg_box"), get_messages());

let socket = io();

socket.on("message", (msg) => {
	//for(const msg of messages.json())
	//console.log(msg);
	let cont = document.getElementById("msg_box");
	cont.appendChild(make_msg(msg)).scrollIntoView();
	cont.removeChild(cont.children[0]);
});


//set a random username or a saved one
var curr_user = document.getElementById("curr_user");

if(localStorage.getItem("username_val_set") == 1)
{
	username_val = localStorage.getItem("username_val");
	curr_user.innerHTML = username_val;
}
else
{
	let result = '';
	let alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	let characters_len = alphabet.length;
	for(let i = 0; i < 12; i++)
	{
		result += alphabet.charAt(Math.floor(Math.random() * characters_len));
	}

	username_val = result;
	curr_user.innerHTML = username_val;
}





let rad = document.getElementsByClassName("bk_rad");

let body = document.getElementsByTagName("body")[0];

rad[0].addEventListener("click", (event) => {
	if(window.getComputedStyle(body).getPropertyValue("background-color") != "rgb(255, 255, 255)")
		body.style.background = "#FFFFFF";
}, {passive: true});
rad[1].addEventListener("click", (event) => {
	if(window.getComputedStyle(body).getPropertyValue("background-color") != "rgb(0, 0, 0)")
		body.style.background = "#000000";
}, {passive: true});

//send on enter
document.getElementById("message").addEventListener("keydown", (event) => {
	if(event.key == "Enter")
		post_message({
			username: username_val,
			message: document.getElementById("message").value
		});

	//event.
});

