#NoEnv
SendMode Event
SetWorkingDir %A_ScriptDir%
SetKeyDelay, 0, 40

FileDelete skip_save_popup

; mute sound during boot
Send {Volume_Mute}
; running the exe directly results in "Steam must be running to play this game" we must launch thru steam url now
; also noted in shaolindrunkard's issue from Feb2017 -- http://forum.arcadecontrols.com/index.php?topic=147402.0
; Run, PACMuseum.exe, %A_WorkingDir% 
Run, steam://rungameid/236470, %A_WorkingDir%

; skip intro, select and launch Pacman Battleroyale
; timings have changed just a bit
Sleep 3000   ; wait for game load
Send {z}{w}  ; skip bandi screen
Sleep 5500   ; wait for intro animation
Send {z}{w}  ; ok at title screen
Sleep 1000   ; wait for dlc popup to draw
Send {z}{w}  ; mrs pacman dlc skip
Sleep 1000   ; wait for dlc popup to undraw
Send {Right} ; move into games and pick battle-royle
Sleep 200
; only 3 up, not 4.  the game order may have changed in latest version
Loop, 3 {
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








