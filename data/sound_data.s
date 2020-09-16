	.section .rodata

	.include "asm/macros/m4a.inc"
	.include "asm/macros/music_voice.inc"

	.include "sound/voice_groups.inc"
	.include "sound/keysplit_tables.inc"
	.include "sound/programmable_wave_data.inc"
	.include "sound/music_player_table.inc"
	.include "sound/song_table.inc"
	.include "sound/direct_sound_data.inc"

@ Things in the above sound data are dependant on memory layout, and
@ screwing with said memory layoug leads to odd musical dissonance.
@ In order to avoid said dissonance, all changes to the music should
@ be placed down here, after the usual music data, and previous forms
@ should be left where they were and unreferenced.

.align 2
voicegroup005:: @ 8676A90
	@ Thanks to Kurausukun for getting me this note 36 sample from their own keyboard
	voice_directsound 60, 0, DirectSoundWaveData_sc88_piano1_36, 255, 253, 0, 241  @ 8676A90
	voice_directsound 60, 0, DirectSoundWaveData_sc88_piano1_48, 255, 252, 0, 239  @ 8676A90
	voice_directsound 60, 0, DirectSoundWaveData_sc88_piano1_60, 255, 250, 0, 221  @ 8676A9C
	voice_directsound 60, 0, DirectSoundWaveData_sc88_piano1_72, 255, 250, 0, 221  @ 8676AA8
	voice_directsound 60, 0, DirectSoundWaveData_sc88_piano1_84, 255, 247, 0, 221  @ 8676AB4

.set KeySplitTable1, . - 15
	.byte 0  @ 15
	.byte 0  @ 16
	.byte 0  @ 17
	.byte 0  @ 18
	.byte 0  @ 19
	.byte 0  @ 20
	.byte 0  @ 21
	.byte 0  @ 22
	.byte 0  @ 23
	.byte 0  @ 24
	.byte 0  @ 25
	.byte 0  @ 26
	.byte 0  @ 27
	.byte 0  @ 28
	.byte 0  @ 29
	.byte 0  @ 30
	.byte 0  @ 31
	.byte 0  @ 32
	.byte 0  @ 33
	.byte 0  @ 34
	.byte 0  @ 35
	.byte 0  @ 36
	.byte 1  @ 37
	.byte 1  @ 38
	.byte 1  @ 39
	.byte 1  @ 40
	.byte 1  @ 41
	.byte 1  @ 42
	.byte 1  @ 43
	.byte 1  @ 44
	.byte 1  @ 45
	.byte 1  @ 46
	.byte 1  @ 47
	.byte 1  @ 48
	.byte 1  @ 49
	.byte 1  @ 50
	.byte 1  @ 51
	.byte 1  @ 52
	.byte 1  @ 53
	.byte 1  @ 54
	.byte 2  @ 55
	.byte 2  @ 56
	.byte 2  @ 57
	.byte 2  @ 58
	.byte 2  @ 59
	.byte 2  @ 60
	.byte 2  @ 61
	.byte 2  @ 62
	.byte 2  @ 63
	.byte 2  @ 64
	.byte 2  @ 65
	.byte 2  @ 66
	.byte 2  @ 67
	.byte 2  @ 68
	.byte 2  @ 69
	.byte 3  @ 70
	.byte 3  @ 71
	.byte 3  @ 72
	.byte 3  @ 73
	.byte 3  @ 74
	.byte 3  @ 75
	.byte 3  @ 76
	.byte 3  @ 77
	.byte 3  @ 78
	.byte 3  @ 79
	.byte 3  @ 80
	.byte 3  @ 81
	.byte 3  @ 82
	.byte 3  @ 83
	.byte 3  @ 84
	.byte 3  @ 85
	.byte 3  @ 86
	.byte 3  @ 87
	.byte 3  @ 88
	.byte 3  @ 89
	.byte 3  @ 90
	.byte 4  @ 91
	.byte 4  @ 92
	.byte 4  @ 93
	.byte 4  @ 94
	.byte 4  @ 95
	.byte 4  @ 96
	.byte 4  @ 97
	.byte 4  @ 98
	.byte 4  @ 99
	.byte 4  @ 100
	.byte 4  @ 101
	.byte 4  @ 102
	.byte 4  @ 103
	.byte 4  @ 104
	.byte 4  @ 105
	.byte 4  @ 106
	.byte 4  @ 107

	.align 2
