License

Copyright (c) 2018 John Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

Any modified versions of the Software, if shared with others, shall not be
shared as official or unmodified versions.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------
 ___               __   ___  __          ___  ___ ___
|   \ |  | |\   | /  \ |    /  \ |\   | |    |    |  \
|   | |  | | \  | |    |--- |  | | \  | |--- |--- |--/
|   | |  | |  \ | |  \ |    |  | |  \ | |    |    | \
|___/ \__/ |   \| \__/ |___ \__/ |   \| |___ |___ |  \

------------------------
       Dungeoneer
  A D&D Text Adventure
  Written in BOTH C++
  And MS Small Basic
------------------------
INFORMATION

There are two versions of Dungeoneer, one written in C++ and the other in SmallBasic.  The C++ source code is available as "dungeoneer.cpp", SmallBasic source code is available as "dungeoneer_sb.sb".  The C++ version executable is "dungeoneer.exe", SmallBasic version executable is "dungeoneer_sb.exe".

Please note that the C++ and SmallBasic versions are BY NO MEANS THE SAME!  The C++ version includes several optimizations over the SmallBasic version in the use of classes and dynamic memory usage, as well as completely different functionality!

Please note that at this point in time the C++ version is only semi-playable due to being incomplete.

Please note that this game is WORK IN PROGRESS.

Please note that this folder is a Mercurial repository committed in TortoiseHG(an upload to GitHub is a possibility, but the GitHub version will not be updated as regularly as the TortoiseHG version).

Please note that "utils.h" is a C++ header file written by me and is covered under the license(it is also necessary to compile a modified version of Dungeoneer if need be).

------------------------
Class Notes: (valid across both versions and D&D)

Fighter
-specializes in dealing melee damage
-highest HP of any class
-high charisma(social skills)

Rogue
-specializes in dealing ranged damage
-Medium HP
-high dexterity

Wizard
-specializes in Magic damage
-LOW HP
-high intelligence

Cleric
-specializes in Magic damage but also has medium melee and ranged damage
-Medium HP
-high intelligence and charisma
-----------------------
Keyboard shortcuts: (for SmallBasic version)

"What would you like to do?" Menu:
1 - Attack/"attack"
2 - Enter a town/"stay a while"
3 - Travel/"move"
4 - Make Camp/"make camp"/"camp"
5 - Forage/"forage"
6 - Scan/"scan"/"scan surroundings" NOTE: this option does not work and (might) crash Dungeoneer

"What would you like to do in town?" Menu:
1 - Buy goods/"buy goods"
2 - Steal something/"steal something"
3 - Leave town/"leave"/"leave town"
4 - Sleep one night/"sleep"
-----------------------
==        C++        ==
-----------------------
Menu inputs:
1 - Attack
2 - Move
3 - Long Rest
4 - Short Rest
5 - Disengage
6 - Scan/Look around
Combat menu inputs
1 - Attack
2 - Dodge
3 - Disengage

Attack Options:
1 - First attack slot
2 - Second attack slot
3 - Third attack slot
---EQUIPMENT BY CLASS--
Fighter----------------
SLOT 1: Longsword 1d8 slashing damage
SLOT 2: Dagger 1d4 piercing damage
SLOT 3: Light Crossbow 1d8 piercing damage
Explorer's Pack
-backpack
-bedroll
-mess kit(food prep supplies)
-10 days rations
-tinderbox
-10 torches
-waterskin
-50 feet of rope
Rogue-----------------
SLOT 1: Shortsword 1d6 slashing damage
SLOT 2: Crossbow 1d10 piercing damage
SLOT 3: Handaxe 1d6 slashing damage
Burglar's Pack
-backpack
-bag of 1000 ball bearings
-crowbar
-hooded lantern
-2 flasks of oil
-10 ft of string
-5 candles
-hammer
-10 pitons
-5 days rations
-tinderbox
-50ft rope
Wizard--------------
SLOT 1: Magic Missile 1d12 + 3 magic damage
SLOT 2: Dagger 1d4 piercing damage
SLOT 3: Fireball 1d6 fire damage
Mage's Pack(not present in D&D but whatever)
-backpack
-materials required to cast fireball spells(balls of bat guano)
-spellcasting focus(either staff or magical weapon)
-10 days rations
-spellbook
Cleric-------------
SLOT 1: Silvered Shortsword 1d8 + 1 slashing damage
SLOT 2: Warhammer 1d8 bludgeoning damage
SLOT 3: Light crossbow 1d8 piercing damage
Priest's Pack(different contents than in D&D but whatever)
-holy water
-holy symbol
-ritual materials
-10 days rations
-long knife
-tinderbox
-urn of relative's ashes