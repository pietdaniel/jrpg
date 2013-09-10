graphic machine
	gets state with objects
	renders to screen

state machine
	map of states
	current state
	update()
	render()
	change()
	push()
	pop()

states : combat, menu, world map, local map

combat state
	actions
	entities
	getActions()
	update()
	render()

menu state
	cursor
	selected
	options
	update
	render
	prevpage

map
	image
	tile_map
	npcs
	character
	foreground
	background
	render()
	update()


world state
	tile map
	char location
	links
	enemies
	update
	render

local state
	tile map
	char location
	links
	npcs
	update
	render

entities
	update()
	render()
	location
	sprite
	name
	description

character
	health
	mana
	atk
	def
	spatk
	spdef
	speed

enemy
	health
	mana 
	atk
	def
	spatk
	spdef
	speed

npc
	dialog
	shop

battle_actions
	attack
	spell
	defend
	item
	run
	decide

action
	target
	origin
	effects
	sprite
	update
	render







