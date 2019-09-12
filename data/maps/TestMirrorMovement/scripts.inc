TestMirrorMovement_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TestMirrorMovement_OnResume
	.byte 0

TestMirrorMovement_OnResume:
	setflag FLAG_PREVENT_EVENT_OBJECT_DESPAWN
	end
