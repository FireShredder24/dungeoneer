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
1 - Attack - Start combat
2 - Move - Travel to a different town
3 - Long Rest - Rest for 8 hours and regain all lost HP
4 - Short Rest - Rest for 1 hour and regain 1d4 HP
5 - Disengage(deprecated, doesn't work)
6 - Scan/Look around - prints a rather useless description of your surroundings
7 - Checkup/Check - prints the items in your inventory and your HP
8 - Eat - consume 1 day's worth of rations
9 - Drink - drink a bit from a bottomless canteen(doesn't work if you don't have a canteen, but doesn't consume canteen either)
10 - Buy Food - Try to find a merchant to sell you rations
11 - Purchase - Try to find a merchant to sell you any item you want (refer to item ID table in the Dungeoneer/docs folder)
12 - Hunt - Search for a wild animal to kill for meat
13 - Sell - Try to find a merchant to buy your goods(this goes in conjunction with hunting, as it can give you money for meat)
------------
-- Cheats --
------------ (input these words, exactly, into the regular menu to get free stuff)
TENDEES! - Instantly gain 1000 food
midas or I_LIKE_GOLD_LLC - Have all of your possessions instantly turned into gold pieces
----------------
-- Boss Fight --
---------------- (input these into main menu)
philswift - Phil Swift, eternal advertising face of the Flex-brand products, descends from heaven and tries to saw you in half! (if you somehow kill him, you get 100 FlexTape!)
flextape - can be used both in combat and out, healing 10 HP for each meter used!

Combat menu inputs
1 - Attack
2 - Dodge
3 - Disengage

Attack Options:
1 - First attack slot
2 - Second attack slot
3 - Third attack slot