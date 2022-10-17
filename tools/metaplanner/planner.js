//-------------------------------------------------------------------
// Data

const hms = {
	"Ct": "Cut",
	"RS": "Rock Smash",
	"St": "Strength",
	"Sf": "Surf",
	"Dv": "Dive",
	"Wf": "Waterfall",
	'#': "PEDESTAL",
	'%': "Scroll",
};

const PARTS = [
	// Placeholder empty room, can be used multiple times, take the place of any other room, supply any one extra HM
	{ id:0, name: "????", exits:["SW","SW","NE","NW","NS","WE","N","S","W","E"], supplies:['#','%',"Ct","RS","St","Sf","Dv","Wf"], requires:[], },
	
	// Puzzle Entrance
	{ id:1, name:"Lavaridge Springs", exits:["ASE", "ASW", "ANS"], supplies:['#'], requires:[], },
	// Final Room
	{ id:2, name:"Final Bluff", exits:["ZW"], supplies:['%'], requires:['%',"Sf","Dv","Wf","RS","St","Ct"], },
	// Can take the place of any corner
	{ id:3, name:"Ice Corner", exits:["SW"], supplies:['#','%','St'], requires:[], }, //requires strength?
	// Enter from bottom, exit anywhere
	{ id:4, name:"Log Flotilla", exits:["SE"], supplies:["Sf"], requires:[], },
	// Ledges down into valley with Rock Smash, use RS to open paths back up and out
	{ id:5, name:"Ledge Valley", exits:["NE"], supplies:["RS",'%'], requires:[], },
	//
	{ id:6, name:"Bike Path", exits:["NS"], supplies:['#','%'], requires:[], },
	//
	{ id:7, name:"Pokemon Stage", exits:["S"], supplies:['#','%',"Ct","St","Dv","Wf","Sf","RS"], requires:[], },
	// The HM ball for Dive shows up twice/two places in the maze, floating on the water, so either end can grab it
	{ id:8, name:"Dive Maze", exits:["NS"], supplies:["Dv"], requires:["Sf"], },
	
	// Guiding Ziggy from above
	{ id:9, name:"Ziggy Room", exits:["SW"], supplies:['%',"Wf","St","Dv","Sf","RS"], requires:["Ct"], },
	// Hidden Maze Redux
	{ id:10, name:"Koga's Elbow", exits:["NW"], supplies:['#','%',"St","RS"], requires:[], },
	//
	{ id:11, name:"Zip Sliding", exits:["WE"], supplies:[], requires:[], }, //TODO Add cut requirement?
	//
	{ id:12, name:"Forest Clearing", exits:["SE"], supplies:['#', "Ct"], requires:[], },
	//
	{ id:13, name:"Berry Breezeway", exits:["NE"], supplies:['#'], requires:[], },
	//
	{ id:14, name:"Subduction Zone", exits:["WE"], supplies:[], requires:['Sf'], },
	//
	{ id:15, name:"15", exits:["NW"], supplies:[], requires:[], },
];

/** 
 * @typedef {Object} InitedRoom
 * @property {number} id
 * @property {string} name
 * @property {string} exits
 * @property {string[]} supplies
 * @property {string[]} requires
 */

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

/** @type {Array<{ $el:HTMLDivElement, def:InitedRoom, id:number }>} */
let GRID = [];
let GRID_SIZE_X = 4, GRID_SIZE_Y = 4;

//-------------------------------------------------------------------
// Setup code

{
	let $list = document.getElementById('left');
	for (let i = 1; i < PARTS.length; i++) {
		let $n = document.createElement('li');
		$n.innerHTML = `<label><input type="checkbox" name="cb${PARTS[i].id}" />${PARTS[i].name}</label>`;
		let $cb = $n.querySelector('input');
		$cb.checked = true; //(i <= 2);
		$cb.disabled = (i <= 2);
		$cb.addEventListener('change', function(ev){
			populateGrid();
		});
		$list.append($n);
	}
	populateGrid();
}

function populateGrid() {
	const $main = document.getElementById('grid');
	const DEFAULT = PARTS[0];
	// empty the grid
	while ($main.firstChild) $main.lastChild.remove();
	$main.classList.remove('size1','size2','size3','size4');
	GRID.length = 0;
	
	let rooms = PARTS.filter((x)=>{
		if (x == DEFAULT) return false;
		let $cb = document.querySelector(`input[name="cb${x.id}"]`);
		return $cb.checked;
	});
	
	rooms = DO_PUZZLE_SETUP_LOGIC(rooms);
	$main.classList.add(`size${GRID_SIZE_Y}`);
	
	let x = 0, y = 1;
	for (let def of rooms) {
		x++;
		if (x > GRID_SIZE_X) { y++; x = 1; }
		if (!def) continue;
		addRoom(def, x, y);
	}
	
	return;
	/**
	 * 
	 * @param {typeof PARTS[0]} def 
	 * @param {number} x 
	 * @param {number} y 
		*/
	function addRoom(def, x, y) {
		let $box = document.createElement('div');
		$box.innerText = def.name;
		$box.classList.add(`loc-${x}x${y}`);
		
		let which = 'enter';
		for (let ex of def.exits) {
			switch (ex) {
				case 'N': $box.classList.add(`${which}-north`); break;
				case 'S': $box.classList.add(`${which}-south`); break;
				case 'E': $box.classList.add(`${which}-east`); break;
				case 'W': $box.classList.add(`${which}-west`); break;
				default: continue;
			}
			which = 'exit';
		}
		
		const $supp = document.createElement('p');
		$supp.classList.add('supplies');
		$supp.innerText = def.supplies.join(', ');
		
		const $req = document.createElement('p');
		$req.classList.add('requires');
		$req.innerText = def.requires.join(', ');
		
		$box.append($supp, $req);
		$box.addEventListener('click', (ev)=>lockRoom(def.id));
		$box.addEventListener('contextmenu', (ev)=>$box.classList.toggle('visited'));
		
		$main.append($box);
		GRID[idx(x-1, y-1)] = { $el:$box, def, id:def.id };
	}
	
	// This will need to be converted into C and inserted into the rom
	/**
	 * 
	 * @param {typeof PARTS} inRooms 
	 * @returns {InitedRoom[]}
	 */
	function DO_PUZZLE_SETUP_LOGIC(inRooms) {
		/** @type {typeof inRooms} */ let ROOMS;
		let numEmptyRooms = 0;
		// Don't have enough rooms, go for the most pathetic
		if (inRooms.length < 3) return logicSize1();
		// If we have enough to go for the largest, go for it
		if (inRooms.length > 10) return logicSize4();
		// Otherwise, start at 9 and drop down if we can't
		return logicSize3();
		/**
		 * 
		 * @param {number} id 
		 * @param {string?} _exits 
		 * @param {string[]?} _supplies 
		 * @param {string[]?} _requires 
		 * @returns {InitedRoom}
		 */
		function initRoom(id, _exits, _supplies, _requires) {
			const room = popRoom(id);
			const exits = _exits || room.exits[0];
			const supplies = _supplies || room.supplies;
			const requires = _requires || room.requires;
			return Object.assign({}, room, { exits, supplies, requires, });
		}
		/**
		 * 
		 * @param {number} id 
		 * @returns {InitedRoom}
		 */
		function popRoom(id) {
			if (id == -1) { // short circuit, would be goto in C
				numEmptyRooms++;
				return Object.assign({}, PARTS[0]); 
			}
			for (let i = 0; i < ROOMS.length; i++) {
				let r = ROOMS[i];
				if (r.id == id) {
					ROOMS.splice(i, 1);
					return r;
				}
			}
			numEmptyRooms++;
			return Object.assign({}, PARTS[0]);
		}
		/**
		 * 
		 * @param {string?} _exits 
		 * @param {string[]?} _supplies 
		 * @param {string[]?} _requires 
		 * @returns {InitedRoom}
		 */
		 function hasRoom(_exits, _supplies, _requires) {
			const matchedRooms = [];
			for (let i = 0; i < ROOMS.length; i++) {
				let r = ROOMS[i];
				let matches = true;
				if (_exits) matches &= r.exits.includes(_exits);
				if (_supplies) 
					for (let sup of _supplies) matches &= r.supplies.includes(sup);
				// if (_requires) 
				// 	for (let req of _requires) matches &= r.requires.includes(req);
				
				if (matches) { matchedRooms.push(r); }
			}
			if (matchedRooms.length == 0) return -1;
			// try and get a native exit pattern
			for (let r of matchedRooms) {
				if (r.exits[0] == _exits) return r.id;
			}
			// otherwise just return the first we found
			return matchedRooms[0].id;
		}
		/**
		 * 
		 * @param {string?} _exits 
		 * @param {string[]?} _supplies 
		 * @param {string[]?} _requires 
		 * @returns {InitedRoom}
		 */
		function findRoom(_exits, _supplies, _requires) {
			return initRoom(hasRoom(_exits, _supplies, _requires), _exits, _supplies, _requires);
		}
		
		function logicSize1() {
			ROOMS = inRooms.slice(); numEmptyRooms = 0; GRID_SIZE_X = 2; GRID_SIZE_Y = 1;
			const grid = [];
			grid.push(initRoom(1, "SE", ['#'], []));
			grid.push(initRoom(2, "W", ['%'], ['%']));
			return grid;
		}
		function logicSize2() {
			ROOMS = inRooms.slice(); numEmptyRooms = 0; GRID_SIZE_X = 2; GRID_SIZE_Y = 2;
			const room1 = initRoom(1, "SN", ['#'], []);
			const room2 = findRoom("SE");
			const room3 = initRoom(2, "W", [], ['%']);
			// If we can't fill that ONE room, drop down to pathetic size
			if (numEmptyRooms > 0) return logicSize1();
			// Adapt the end room as needed
			if (!room2.supplies.includes('%')) {
				// ROM: Insert flags for bypasses here
				room3.supplies.push('%');
			}
			const grid = [
				room3, undefined,
				room2, room1,
			];
			return grid;
		}
		function logicSize3() {
			ROOMS = inRooms.slice(); numEmptyRooms = 0; GRID_SIZE_X = 3; GRID_SIZE_Y = 3;
			const roomEx = initRoom(2, "W", [], ['%']);
			const roomEn = initRoom(1, "SE", ['#'], []);
			const roomNW = findRoom("NW");
			const roomNS = findRoom("NS", ['#']);
			const roomSW = findRoom("SW", ['#']);
			const roomSE = findRoom("SE");
			const roomNE = findRoom("NE", ['#']);
			const roomWE = findRoom("WE");
			
			// If we've got too many empty rooms, try smaller
			if (numEmptyRooms > 4) return logicSize2();
			
			const grid = [
				roomSE, roomNE, roomWE,
				roomEx, roomNS, roomNW,
				roomSW, roomEn, undefined,
			];
			return grid;
			return ROOMS.map(x=>Object.assign({}, x, { exits:x.exits[0] }));
		}
		function logicSize4() {
			ROOMS = inRooms.slice(); numEmptyRooms = 0; GRID_SIZE_X = 4; GRID_SIZE_Y = 4;
			const room1 = initRoom(13, "NE", ['#']);
			const room2 = initRoom(4, 'SE', ['Sf']);
			const room3 = initRoom(2, "W", []); // Exit
			const room4 = initRoom(7, "S", ['%']); // Pokemon Stage
			
			const room5 = initRoom(9, "SW", ['Wf'], ['Ct']); // Ziggy's Room
			const room6 = initRoom(3, "SW", ['St']); // Ice Corner
			const room7 = initRoom(15, "NW", []);
			const room8 = initRoom(14, "WE");
			
			const room9 = initRoom(8, "NS", ['Dv'], ['Sf']);
			const roomA = initRoom(6, "NS", ['#']); // Bike Path
			const roomB = initRoom(12, "SE", ['#', 'Ct']); // Forest Clearing
			const roomC = initRoom(10, "NW", []); // Koga's Elbow
			
			const roomD = initRoom(5, "NE", ['RS']); // Ledge Valley
			const roomE = initRoom(11, "WE", []); // Zip Sliding
			const roomF = initRoom(1, "SE", ['#'], []); // Entrance
			
			// If we've got too many empty rooms (somehow), go smaller
			// Note, this should never be true if we did the prerequisite logic at the top correctly
			if (numEmptyRooms > 7) return logicSize3();
			// TODO
			const grid = [
				room1, room2, room3, room4,
				room5, room6, room7, room8,
				room9, roomA, roomB, roomC,
				roomD, roomE, roomF, undefined,
			];
			return grid;
			return ROOMS.map(x=>Object.assign({}, x, { exits:x.exits[0] }));
		}
		
	}
}

//-------------------------------------------------------------------
// Play code
let currLock = -1;

function findFreeSpace() {
	for (let y = 0; y < GRID_SIZE_Y; y++) {
		for (let x = 0; x < GRID_SIZE_X; x++) {
			let i = idx(x, y);
			if (!GRID[i]) return { i, x, y };
		}
	}
}

function swapLocs(ax, ay, bx, by) {
	if (idx(ax, ay) == currLock || idx(bx, by) == currLock) return; // do nothing
	let temp = GRID[idx(ax,ay)];
	GRID[idx(ax,ay)] = GRID[idx(bx,by)];
	GRID[idx(bx,by)] = temp;
	
	let $a, $b;
	if ($a = GRID[idx(ax,ay)]) {
		$a.$el.classList.remove(`loc-${bx+1}x${by+1}`);
		$a.$el.classList.add(`loc-${ax+1}x${ay+1}`);
	}
	if ($b = GRID[idx(bx,by)]) {
		$b.$el.classList.remove(`loc-${ax+1}x${ay+1}`);
		$b.$el.classList.add(`loc-${bx+1}x${by+1}`);
	}
}

document.addEventListener('keydown', function(ev) {
	const { x:fx, y:fy } = findFreeSpace();
	console.log(`keydown=${ev.code} freeSpace=(${fx},${fy})`);
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
		case "KeyR": // Reset
			currLock = -1;
			populateGrid();
			break;
	}
});

function lockRoom(id) {
	if (currLock > -1) {
		GRID[currLock].$el.classList.remove('locked');
		currLock = -1;
	}
	let x = GRID.findIndex(x=>x && x.id == id);
	if (x > -1) {
		currLock = x;
		GRID[currLock].$el.classList.add('locked');
	}
}

function idx(x, y) { return (y*GRID_SIZE_X) + x; }