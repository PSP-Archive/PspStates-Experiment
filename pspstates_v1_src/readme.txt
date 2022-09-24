PspStates Experiment for PSP SLIM
---------------------------------

Please read carefully this book... i mean this readme before proceeding to use this plugin.

Note: The author will not be responsable of any kind of damage to units or of data loss
(including game data loss) that this software may cause.
This is true for all my software as they are free, but in this case I would feel like I
would indicate it explicitily.
It is recommended that you backup the nand and important data of memory stick before using this plugin, in order to avoid posible loss of data.

This program was never intended to be part of M33 cfw, it always was planned to be released as
a plugin, just to clarify :)

This software is experimental work and it may behave incorrectly or not work in all cases.

Requisites:
-----------

- 4.01 M33, 1 or 2, doesn't matter.
- A good memory stick is recommended. Fake memory sticks are... fake... and shit, they could make
load and savestate too slow.

Instructions:
-------------

Copy seplugins folder content (IMPORTANT: including the empty folder SAVESTATE, as the plugin will not create it) in /seplugins and activate the plugin using the recovery.

This plugin at the moment will only work in game mode, don't bother to use it in pops or vsh.

VERY IMPORTANT: because of technical reasons, DO NOT USE this plugins with umd's inserted,
and do not use it of course with UMD's in normal mode, even isofs mode is not recommended.
Use only in march33 (recommended), np9660 or in homebrew.
You can have the plugin loaded in umd's, as soon as YOU DON'T USE IT.

SaveState procedure:
--------------------

- To save a state, press the home button in game, and once in the home button screen, press R
plus one of the followings buttons: up, down, right, left, square, triangle, cross, circle or start. Each of this button is considered a "slot", so you can have up to 9 states.
At the moment these state are global: this means they are for all games, not for a specific one.

- At that moment, the PSP will go to sleep mode and return automatically inmediately.

- After the quick sleep mode return, you will see a black screen for some seconds, don't worry it will end. The time can vary depending of games and cpu speed, at this state the program is copying ram from one place to another.

- When the screen is turned on again, you will see the memory stick led blinking for some time: this is the write of the file. If your memory stick is good, this step should be quick.

- The state is saved, it can be loaded during the game or in another game session. (if memory sitck is same or with similar content, you can load other game states withing a game).

The state is saved to one of the followings files:

ms0:/seplugins/SAVESTATE/globalstate_u.bin -> up button
ms0:/seplugins/SAVESTATE/globalstate_d.bin -> down button
ms0:/seplugins/SAVESTATE/globalstate_l.bin -> left button
ms0:/seplugins/SAVESTATE/globalstate_r.bin -> right button
ms0:/seplugins/SAVESTATE/globalstate_q.bin -> square button
ms0:/seplugins/SAVESTATE/globalstate_t.bin -> triangle button
ms0:/seplugins/SAVESTATE/globalstate_x.bin -> cross button
ms0:/seplugins/SAVESTATE/globalstate_c.bin -> circle button
ms0:/seplugins/SAVESTATE/globalstate_s.bin -> start button

The size of the file may vary depending of the game, as it is a 36 MB dump compressed.
Tests show that the most expected range is: 10-20 MB. The plugin will not check free space,
you are on your own on that.

LoadState procedure:
--------------------

- To load a state, press the home button in a game, and once in the home button scree, press L
plus one of the slot buttons mentioned in savestates.

- In that moment, the memory stick led will blink. This step should be fast on good memory sticks.
- After that, the psp will go to sleep mode and return automatically quickly.
- The screen will be black for some moment, this wait moment is much faster than the one for savestates.
- Once the screen is turned on, and if all went fine, your system will be now in the state in which you saved it.

Comments
--------

- The current release is a 4.01 M33 specific plugin. It won't work in a future firmware without an update, unless that firmware has highly similarities with 4.01.

- For faster operation, it is recomended that you set speed to 333 for game in vshmenu or recovery.

- You can load the state of any other iso or homebrew, as soon as they are really in the same memory stick. Do not change name or path of isos or homebrews after you have saved a state of that iso or homebrew, or the load state will not work properly (would probably work for some moment until game try to load data from ms). Anyways, in some cases, in prevision of hardware 
related problems it is more recommended to load states only from the same game.

- A load state is a REAL LOAD STATE with all the consequences.
  Lets say you are playing an iso game in march33 mode with the plugin X activated and plugin 
  Y desactivated.
  Then, in another sesion you are playing that game (or another, as doesn't matter), in
  np9660 mode with the plugin X desactivated and the plugin Y activated. When you load the state,
  the game that was saved will still be in march33 mode with plugin X activated and Y plugin
  desactivated.
  Because the load state even restores the own pspstates plugin itself, this also causes the
  "plugin self-downgrading" problem commented later.

- This plugin is not compatible with any homebrew or plugin using the memory extended size of the slim. It can be enabled while using them, but it SHOULD NOT BE USED.

Interoperability
----------------

- Interoperability between different sony version numbers: this won't be supported, technical reasons. If you were in let's say in a future 4.10 M33 and you want to load a state saved in 4.01 M33, even if the plugin is updated to work on 4.10 M33, it will probably crash loading that state.

- Interoperability between different M33 version numbers (4.01 M33, M33-2, M33-3...): there shouldn't be problem with this. After load state, the system would be temporally downgraded in ram, until you exit to vsh.

- Interoperability with future versions. Because this software is still experimental, future versions could change savestate data format. Even if it doesn't change, the "plugin self downgrading" problem still exists: you have saved a state in version 1, and then you load it
in version 2, the plugin in ram after the load state will be the version 1.

- Interoperability with other psp's. Probably not a good idea to share savestates between psp's... they could cause hardware incorrect answer or data loss. The only test done has been PSP1: TA-085, PSP2: TA-085 v2. The PSP1 saved the state.
The PSP2 loaded the state. The state load apparently worked, but the game, which was controlled
by analogic pad, wasn't answering properly to controls. Wether this was caused by different mother boards or other reasons it is unknown.
Anyways if you want to proceed to do more tests, do it on your own, but have in mind some things:

* Functional issues: the hardware should be the more similar possible. The isos or homebrews 
  should have same paths. Better not to have another plugin activated.

* Privacy issues: The savedata may contain in plain text or compressed, wep or wpa keys. Also,
  if the XMB didn't clear properly the ram, there exist the possibility too of the savedata
  containing filenames or even binary data of media that was played in the XMB, which can
  be recovered using computer forensics.


FAQ
----

Q: Why only PSP SLIM?
A: In the current implementation, I'm using slim extra memory. The file writing is post-poned
while file read is done before the real load state. This is because we lack of a good memory
stick driver that could be used in situations where the kernel is off. The only memory stick
driver we have, which is the used in DC, is extremelly slow, it has no sense to use it here. Until memory stick dma code is reversed, it is impossible the implementation on psp phat.

Q: After doing a savestate, sound stopped working
A: try to load the state you just saved to see if this fixes. This may happen sometimes in
some games, it is not 100% sure, but the reason identified in tests seems to be: the write of the file. In the current implementation,the plugin performs the real savestate after returning from the induced sleep mode code, compressing it in from one ram to temporal one, then original sleep mode return code is executed,and when the system is stable, the file is written. It seems some games or some sony code may not like that such a big file is written, probably due to the time it may take. 
If some day, the DMA memory stick driver is reversed, this problem should be gone too... hopefully :)

Third party licenses
--------------------

This program uses the FastLZ library, which is relased under MIT license. A copy
of the license can be found at fastlz_license directory.


