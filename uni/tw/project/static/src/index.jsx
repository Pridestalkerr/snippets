
function show_entry(id)
{
	fetch("/database/entries.json").then(function(response){
		return response.json();
	}).then(function(data){
		let entries = data.entries;
		//add stuff
	});
	document.getElementById("entry_container").classList.add("visible");
}

let entries_id = document.getElementsByClassName("entry");

console.log(entries_id);

for(let itr = 0; itr < entries_id.length; ++itr)
{
	entries_id[itr].onclick = function(){
		show_entry(this.id);
	}
}
