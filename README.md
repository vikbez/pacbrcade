# PACBRCADE

## Info

This is a mod for having a Pacman BattleRoyale game that is like it's arcade version. Based on Pacman Museum (PC version).

## THIS PROJECT IS ARCHIVED
[Please look here](http://www.emuline.org/topic/1252-tuto-ameliorations-pac-man-battle-royale/) for a more up-to-date patch !

From this:
![before](/assets/before.jpg)

To this:
![after](/assets/after.jpg)

This mod consists of a few things:

- A d3d9.dll proxy that does some modifications to the game: bezel removal, 180 degree rotation of players 3 and 4, hiding the boot menus, and checking for some dialog boxes to bypass (thanks [Michael Koch](http://www.codeguru.com/cpp/g-m/directx/directx8/article.php/c11453/Intercept-Calls-to-DirectX-with-a-Proxy-DLL.htm) for your tutorial).

- [x360ce](https://github.com/x360ce/x360ce) (that adds xinput1_3.dll) for using other input devices than xbox360 controllers ones (or any usb hid interface for controls)

- An AutoHotKey script (RUNME.ahk / RUNME.exe) that automatically goes into the game without anything to do (simulates key press to select game in menu), that mutes sound when doing this, and that press player1's A button when "game saved" popup is here (but hidden by d3d9.dll proxy).

The official Pacman BattleRoyale cocktail game cabinet uses [namco system 147 hardware](http://www.system16.com/hardware.php?id=981) which is based on Playstation 2 hardware, and uses a 32" screen at 1280x720 resolution.

## Usage:

- Buy 4 usb SNES controllers from china on ebay (should be 3$ each with shipping)
- Extract the [latest PACBRCADE release archive](https://github.com/vikbez/pacbrcade/releases/latest) to your Pacman Museum installation folder.
- Configure all 4 players inputs (with x360ce.exe): each player needs up, down, left, right and A button (A button is used as start button ingame)
- Configure player 1 X and B buttons: X opens config menu (for setting round number, speed, etc) (menu works only during title screen) and B button exits this menu
- Run using RUNME.exe (which is the compiled RUNME.ahk script)

## Non-rotated version (aka Deluxe (upright) version):

- rename d3d9-norotate.dll to d3d9.dll
- rename loading-norotate.png to loading.png

## Known bugs / todo:

- Find a way to open the service menu: if you use a disassembler on PACMuseum.exe, you will see that the arcade menu stuff is in here. I don't know how to do this.
- Sometimes you may get an achievement when launching pacman museum, stopping the auto selection of the game. You will then have to navigate in the menus to launch BattleRoyale with player 1 controls.
- If you have multiple screens, this may crash at launch !

## Credits

[vik](http://github.com/vikbez)
