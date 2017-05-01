#NoEnv
SendMode Event
SetWorkingDir %A_ScriptDir%
SetKeyDelay, 0, 40

FileDelete skip_save_popup

; mute sound during boot
Send {Volume_Mute}
Run, PACMuseum.exe, %A_WorkingDir%

; skip intro, select and launch Pacman Battleroyale
Sleep 3000
Send {z}{w}
Sleep 5500
Send {z}{w}
Sleep 250
Send {Right}
Sleep 200
Loop, 4 {
	Send {Up}
	Sleep 100
}
Send {z}{w}

; unmute
Sleep 500
Send {Volume_Mute}

; Bypass "progress have been saved" screen
; sorry for this method, but GetPixelColor does not work on this game
; d3d9.dll creates a file named skip_save_popup when it needs to draw
; the popup, so we know when to send a key to bypass the popup
while WinExist("ahk_class PACMuseum") {
	if FileExist("skip_save_popup") {
		FileDelete skip_save_popup
		; mute volume so we do not hear the "ting" when we press A
		; this is commented because sometimes the Volume_Mute command does
		; random things as "menu open" button in game
		; Send {Volume_Mute}
		Send {z}{w}
		Sleep 400
		; Send {Volume_Mute}
	}
	Sleep 500
}

Exit








