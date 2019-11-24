
function show_menu()
{
	let nav2 = document.getElementById('nav2');
	if(nav2.classList.contains('visible'))
		nav2.classList.remove('visible')
	else
		nav2.classList.add('visible')
}


function get_entries(is_new, is_top, count)
{
    return new Promise(function(resolve, reject){
        fetch("/database/entries.json").then(function(response){
            response.json().then(function(data){
                let entries = data.entries;	//entry.new === is_new && entry.top === is_top
                resolve(entries.filter(entry => ((is_new && entry.new) || (is_top && entry.top)) && count-- > 0));
            }).catch(reject);
         }).catch(reject)
    });
}

function show_entry(entry)
{
	let container = document.getElementById("entry_container");
	let main = container.children[0];

	let poster = main.appendChild(document.createElement("img"));
	poster.src = entry.getAttribute("data-img_large");
	poster.id = "entry_poster";

	let content = main.appendChild(document.createElement("div"));
	content.id = "entry_content";
	content.appendChild(document.createElement("h1")).innerHTML = entry.getAttribute("title");

	let video = content.appendChild(document.createElement("iframe"));
	video.width = "800";
	video.height = "600";
	video.src = entry.getAttribute("data-video");

	content.appendChild(document.createElement("article")).innerHTML = entry.getAttribute("data-plot");

	container.classList.add("visible");
	container.onclick = function(){
		container.classList.remove("visible");
		main.removeChild(poster);
		main.removeChild(content);
	};
}

function make_entry(entry)
{
	let element = document.createElement("td");

	element.setAttribute("title", entry.title)
	element.setAttribute("data-video", entry.video);
	element.setAttribute("data-plot", entry.plot);
	element.setAttribute("data-img_large", entry.img_large);

	let fig = element.appendChild(document.createElement("figure"));
	//fig.classList.add("entry")
	fig.appendChild(document.createElement("figcaption")).innerHTML = entry.title;
	fig.appendChild(document.createElement("br"));
	fig.appendChild(document.createElement("img")).src = entry.img;

	//add the onclick in here, kinda ugly but whatever
	element.onclick = function(){
		show_entry(element);
	};

	return element;
}

function insert_entries(table_element, entries)
{
	if(table_element === null)
		return;
	//console.log(table_element);
	let row = table_element.appendChild(document.createElement("tr"));
	for(let itr = 0; itr < entries.length; ++itr)
	{
		row.appendChild(make_entry(entries[itr]));
	}
}


if(window.location.pathname === "/")
{
	get_entries(true, false, 5).then(function (entries){
		insert_entries(document.getElementById("new_slider"), entries);
	});

	get_entries(false, true, 5).then(function (entries){
		insert_entries(document.getElementById("top_slider"), entries);
	});
}
else if(window.location.pathname === "/pages/news.html")
{
	get_entries(true, false, 30).then(function (entries){
		//5*6
		let table = document.getElementById("entry_table");
		for(let itr = 0; itr < 6; ++itr)
		{
			insert_entries(table, entries.slice(itr * 5, itr * 5 + 5));
		}
	});
}
else if(window.location.pathname === "/pages/top.html")
{
	get_entries(false, true, 30).then(function (entries){
		//5*6
		let table = document.getElementById("entry_table");
		for(let itr = 0; itr < 6; ++itr)
		{
			insert_entries(table, entries.slice(itr * 5, itr * 5 + 5));
		}
	});
}
else
{
	//list all
	get_entries(true, true, 30).then(function (entries){
		//5*6
		let table = document.getElementById("entry_table");
		for(let itr = 0; itr < 6; ++itr)
		{
			insert_entries(table, entries.slice(itr * 5, itr * 5 + 5));
		}
	});
}

