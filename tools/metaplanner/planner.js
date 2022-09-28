
const hms = {
	"Ct": "Cut",
	"RS": "Rock Smash",
	"St": "Strength",
	"Sf": "Surf",
	"Dv": "Dive",
	"Wf": "Waterfall",
	"PD": "PEDESTAL",
	"Sc": "Scroll",
};

const parts = [
	// Placeholder, can be used multiple times, take the place of any other room, supply any one extra HM
	{ id:"r0", name: "????", exits:["SW","SW","NE","NW","NS","WE","N","S","W","E"], supplies:["Ct","RS","St","Sf","Dv","Wf"], requires:[], },
	
	// Puzzle Entrance
	{ id:"r1", name:"Lavaridge Springs", exits:["ASE", "ASW", "ANS"], supplies:["PD"], requires:[], },
	// Final Room
	{ id:"r2", name:"Final Bluff", exits:["ZW"], supplies:["Sc"], requires:["Sf","Dv","Wf","RS","St","Ct"], },
	// Can take the place of any corner
	{ id:"r3", name:"Ice Corner", exits:["SW","SE","NE","NW"], supplies:["PD"], requires:[], }, //requires strength?
	// Enter from bottom, exit anywhere
	{ id:"r4", name:"Log Flotilla", exits:["SE","SW","NS"], supplies:["Sf"], requires:[], },
	// Ledges down into valley with Rock Smash, use RS to open paths back up and out
	{ id:"r5", name:"Ledge Valley", exits:["SE"], supplies:["RS"], requires:[], },
	//
	{ id:"r6", name:"Bike Path", exits:["NS"], supplies:["PD"], requires:[], },
	//
	{ id:"r7", name:"Pokemon Stage", exits:["S","W","E"], supplies:["PD","Sc","Ct","St","Dv","Wf","Sf","RS"], requires:[], },
	// The HM ball for Dive shows up twice/two places in the maze, floating on the water, so either end can grab it
	{ id:"r8", name:"Dive Maze", exits:["NS"], supplies:["Dv"], requires:["Sf"], },
	
	// Guiding Ziggy from above
	{ id:"r9", name:"Ziggy Room", exits:["SW","NE","NW","SE"], supplies:["Wf","St","Dv","Sf","RS"], requires:["Ct"], },
	// Hidden Maze Redux
	{ id:"r10", name:"Koga's Elbow", exits:["NW","NE","SW","SE"], supplies:["PD","St","RS"], requires:[], },
	//
	{ id:"r11", name:"Zip Sliding", exits:["WE"], supplies:[], requires:[], },
	//
	{ id:"r12", name:"Forest Clearing", exits:["NW"], supplies:["Ct"], requires:[], },
	//
	{ id:"r13", name:"13", exits:["NE"], supplies:[], requires:[], },
	//
	{ id:"r14", name:"14", exits:["WE"], supplies:[], requires:[], },
	//
	{ id:"r15", name:"15", exits:["NE"], supplies:[], requires:[], },
];

const numToLayout = [];
numToLayout[0] = "empty";
numToLayout[1] = "empty";
numToLayout[2] = "2x1";
numToLayout[3] = "2x2";
numToLayout[4] = "2x2";
numToLayout[5] = "3x3";
numToLayout[6] = "3x3";
numToLayout[7] = "3x3";
numToLayout[8] = "3x3";
numToLayout[9] = "3x3";
numToLayout[10]= "3x3";
numToLayout[11]= "3x3";
numToLayout[12]= "4x4";
numToLayout[13]= "4x4";
numToLayout[14]= "4x4";
numToLayout[15]= "4x4";

const layouts = {
	"empty": null,
	"2x1": { w:2, h:1, layout:[
		"ASE","ZW"
	]},
	"2x2": { w:2, h:2, layout:[
		"ZW", " ",
		"SE","ANS",
	]},
	"3x3": { w:3, h:3, layout:[
		"SE","NE","WE",
		"ZW","NS","NW",
		"SW","ASE"," ",
	]},
	"4x4": { w:4, h:4, layout:[
		"NW","SE","ZW","N",
		"SE","NE","WE","S",
		"NS","SW","SE","NW",
		"NE","WE","ASE"," ",
	]},
};

/** @type {Array<{ $el:HTMLDivElement }>} */
let GRID = [];
let GRID_SIZE_X = 4, GRID_SIZE_Y = 4;

//-------------------------------------------------------------------

{
	let $list = document.getElementById('left');
	for (let i = 1; i < 15; i++) {
		let $n = document.createElement('li');
		$n.innerHTML = `<label><input type="checkbox" name="l${i}" checked/>${parts[i].name}</label>`;
		$list.append($n);
	}
}

{
	const $main = document.getElementById('grid');
	let x = 0, y = 1;
	const DEFAULT = parts[0];
	
	
	
	for (let def of parts) {
		if (def == DEFAULT) continue;
		x++;
		if (x > GRID_SIZE_X) { y++; x = 1; }
		addRoom(def, x, y);
	}
	
	/**
	 * 
	 * @param {typeof parts[0]} def 
	 * @param {number} x 
	 * @param {number} y 
		*/
	function addRoom(def, x, y) {
		let $box = document.createElement('div');
		$box.innerText = def.name;
		$box.classList.add(`loc-${x}x${y}`);
		
		let exits = def.exits[0]
		let which = 'enter';
		for (let ex of exits) {
			switch (ex) {
				case 'N': $box.classList.add(`${which}-north`); break;
				case 'S': $box.classList.add(`${which}-south`); break;
				case 'E': $box.classList.add(`${which}-east`); break;
				case 'W': $box.classList.add(`${which}-west`); break;
				default: continue;
			}
			which = 'exit';
		}
		
		for (let s of def.supplies) {
			const $s = document.createElement('em');
			$s.classList.add(s);
			$box.append($s);
			if (s != 'PD') break;
		}
		
		$main.append($box);
		GRID[(y*GRID_SIZE_Y)+x] = { $el:$box };
	}
}

function findFreeSpace() {
	for (let y = 0; y < GRID_SIZE_Y; y++) {
		for (let x = 0; x < GRID_SIZE_X; x++) {
			let i = (y * GRID_SIZE_X) + x;
			if (!GRID[i]) return { i, x, y };
		}
	}
}

function swapLocs(ax, ay, bx, by) {
	let temp = GRID[(ay*GRID_SIZE_X)+ax];
	GRID[(ay*GRID_SIZE_X)+ax] = GRID[(by*GRID_SIZE_X)+bx];
	GRID[(by*GRID_SIZE_X)+bx] = temp;
	
	let $a, $b;
	if ($a = GRID[(ay*GRID_SIZE_X)+ax]) {
		$a.$el.classList.remove(`loc-${bx+1}x${by+1}`);
		$a.$el.classList.add(`loc-${ax+1}x${ay+1}`);
	}
	if ($b = GRID[(by*GRID_SIZE_X)+bx]) {
		$b.$el.classList.remove(`loc-${ax+1}x${ay+1}`);
		$b.$el.classList.add(`loc-${bx+1}x${by+1}`);
	}
}

document.addEventListener('keydown', function(ev) {
	const { x:fx, y:fy } = findFreeSpace();
	switch (ev.code) {
		case "ArrowDown":
			if (fy-1 >= 0 && fy-1 < GRID_SIZE_Y) {
				swapLocs(fx, fy, fx, fy-1);
			}
			break;
		case "ArrowUp":
			if (fy+1 >= 0 && fy+1 < GRID_SIZE_Y) {
				swapLocs(fx, fy, fx, fy+1);
			}
			break;
		case "ArrowLeft":
			if (fx+1 >= 0 && fx+1 < GRID_SIZE_X) {
				swapLocs(fx, fy, fx+1, fy);
			}
			break;
		case "ArrowRight":
			if (fx-1 >= 0 && fx-1 < GRID_SIZE_X) {
				swapLocs(fx, fy, fx-1, fy);
			}
			break;
	}
});

