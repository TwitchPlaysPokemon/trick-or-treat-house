# Trick-Or-Treat House

A ROM hack based on the [Pokémon Emerald decompilation project.](https://github.com/pret/pokeemerald).

This hack has many special things for making new Trick House Puzzles. A Trick House Puzzle is defined as such:

1. Has an entry point marked by a door, midpoint marked by a scroll, and endpoint marked by a stone door.
2. Is usually a maze or puzzle based on movement and/or opening the way forward.
3. May contain trainers to hinder progress or punish wrong movement.

This ROM has a framework for modularly supporting hundreds of these puzzles independantly of one another. It also has a simple framing story as a simple vehicle for getting the player into the puzzles as quick as possible.

The Trick House itself is modified such that the player gets a team of three rental Pokemon and then heads into the puzzle with a short introduction from the Trick Master (or supporting character). The puzzle itself is very flexable, allowing any kind of map(s) to be used, as long as there's an entry point as the startpoint, a scroll as a midpoint, and a stone door as an endpoint. Once the puzzle is completed, the player is taken through the stone door back to the Trick House's back room, where a character related to the puzzle can give any sort of quip about the puzzle they like, before the player's party is healed and they're sent back around to the front corridor of the Trick House to move on to the next puzzle.

## How to Define a Puzzle

A puzzle is identified by its first (or only) map. The ID of this map is put into an ordered list of puzzles. The map header will be referenced by the framework for many things. A puzzle can have the following information given in the puzzle's map script header.

- Puzzle Name (required): A pithy name for the puzzle. This will be shown upon first entering the puzzle's map from the Trick House, in the same way a route's name would be shown upon entering it.
- Puzzle Author: The name of the maker of the puzzle. If a name is not given, the Trick Master will claim ownership of it.
- Adjective: An adjective used by the Trick Master when describing the puzzle in his introduction text.
- Quip: A block of text used by the character in the end room (by default the Trick Master) when the player speaks with them.
- Prerequisite Item List: A list of item ids the Trick Master should give the player during his introduction. By default, nothing is given.
	- Use this list to give HM Items if your puzzle requires it.
- Post Clean Up Item List: A list of item ids to take from the player after the puzzle ends. By default, nothing is taken.
	- Use this list to take any HM Items from the player that were given to them before or during the puzzle. Clean up after yourself, please.
- Meta Variable List: A list of variables and what they should be set to. This will be called by the framework mainly to set the graphic of the Trick Master in the front corridor, and the quip character in the back corridor. By default they're both the Trick Master, but they can be set to anyone by the puzzle.
- Setup Script: This script is run in addition to any other map introduction scripts when the player enters a puzzle for the first time.
- Teardown Script: This script is run before warping to the back room of the Trick House, before the puzzle's last room is unloaded.

In addition to the above map script header information, the following can be defined by or used by the puzzle.

- Trainers are no longer defined in one place anymore. A map can define up to 50 of its own trainers in the map header. See below for format.
	- These trainers are defined in `trainers.json`, which is compiled into a trainer and party table in the map header.
	- A map header can point to another map's trainer table. This can be done by assigning the pointer manually in the map.json of a map to point at another map's table. The pointer name is of the format `<MapName>_TrainerTable`.
- If the tileset of the puzzle does not allow use of the trick house tileset, the puzzle designer can use some event objects defined for such a situation.
	- An entrance mat event object has been specially coded so the player can walk over it. Place it on the usual southern arrow warp tiles and warp to allow the player to exit the puzzle via the entry point.
	- Two scroll doors, one set into a wall and one into a little room, are available for use. 
		- These objects are coded specially to align to the tile grid like a normal door, despite the look in porymap. The door will be on the tile its object is centered on.
		- If you give these doors a "trainerType" of 5 (or "BUMP INTERACTION" if using the proper version of porymap), then they can act like animated doors and will allow the player through when bumped into. Be sure to put collision around the door, otherwise the player will be able to walk through the walls on either side of the door object.
	- Two stone doors, one set into a wall and one into a little room, are available for use, for the end of level doorways.
		- The same things apply to these as they do to the scroll door objects.
- A selection of flags and vars have been cleared out for use by puzzles. These will be cleared upon moving to the next puzzle.
- The use of common scripts for scrolls and exit doors is encouraged. See trick_house.inc

## Trainers.json

```js
[
	{
		"class": "YOUNGSTER", // Trainer class, prepended with "TRAINER_CLASS_". Required.
		"name": "JOEY", // Required.
		"music": "INTENSE", // Prepended with "TRAINER_ENCOUNTER_MUSIC_"
		"female": false, // If true, sets the female flag.
		"pic": "YOUNGSTER", // Trainer pic, Prepended with "TRAINER_PIC_". Defaults to the same as "class".
		"items": ["ITEM_POTION"], // Up to 4 items.
		"doubleBattle": false, //
		"aiFlags": "AI_SCRIPT_CHECK_BAD_MOVE", // Pasted as-is into the data. Defaults to AI_SCRIPT_CHECK_BAD_MOVE if not present.
		"party": [
			{
				"species": "SPECIES_RATTATA", // Required
				"level": 10, //Required
				"iv": 0, //Defaults to 0.
				"item": "ITEM_BERRY", // If present, makes the trainer's party a custom item party. Defaults to ITEM_NONE in that case.
				"moves": [ // If present, makes the trainer's party a custom move party. All pokemon must have custom moves if any do.
					"MOVE_TACKLE",
					// Up to 4 moves.
					// Remaining moves default to "MOVE_NONE"
				],
			}
		],
	}
]
```

## Restrictions

- Never use the Rival character, in a puzzle or in the framework around it. Also be careful using legendary Pokemon. The puzzle event objects utalize the same special palette slot as the rival character or legendary Pokemon, and thus will cause palette clashes if used together.
