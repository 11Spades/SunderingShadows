
#include <std.h>

#include "/d/stella/short.h"

inherit ROOM;
int gargoyle_gone;

void init(){
	::init();
        add_action("summon_guardian","summon");
	}

void reset(){
        ::reset();
	gargoyle_gone = 0;
	add_item("gargoyle","This is an unusual gargoyle!  It looks like a scorpion poised to strike!");
	add_item("scorpion","This is an unusual gargoyle!  It looks like a scorpion poised to strike!");
	}

void create(){
      ::create();
      set_property("light",2);
      set_terrain(VILLAGE);
      set_travel(PAVED_ROAD);
      set_name("Tower Roof");
      set_short("%^BLUE%^Tower Roof");
      set_long(
	     "%^BLUE%^You are on the roof of one of the towers!  It is pretty empty here "
	     "except for a stone gargoyle.  You have an incredible view from "
	     "up here.  To the outside you see down into the tower gardens and "
	     "to the inside the courtyard with it's dome-shaped building. "
      );
      set_listen("default",
        "You can still hear faint bird song from the garden."
      );
      set_smell("default",
        "."
      );
      set_items(([
	({"scorpion","gargoyle"}):"This is an unusual gargoyle!  It looks like a scorpion poised to strike!",
	"floor":"You lok down at the floor and notice a trapdoor!",
	"trapdoor":"This is the way back into the tower",
        "courtyard":"From here, the courtyard looks as deserted except for a dome-shaped building",
	({"dome","building","dome shaped building"}):"The dome seems to made of a single hemisphere "
	   "shaped piece of black marble.  The dome has been intricately carved but you can't see much "
	   "detail from here.  Strangely, the building has no visible windows.  ",
	"garden":"You look down into a beautiful garden containing a variety of flowers."
       ]));
      set_exits(([
	 "trapdoor": RPATH "towerup4"
       ]));
      set_pre_exit_functions( ({"trapdoor"}), ({"go_down"}) );
      gargoyle_gone = 0;
      }

int go_down(){
      tell_object(TP,"You climb down from the roof through a trapdoor.");
      say(TPQCN+ " climbs through a trapdoor.",TP);
      return 1;
}

int summon_guardian(string str){

if ((str=="scorpio")&&(!gargoyle_gone)){
  say("\n%^BOLD%^As the name \"Scorpio\" is spoken, the air shimmers around "
              "the odd gargoyle. \n"
              "The gargoyle comes to life!!\n\n"
              "Scorpio turns to "+TPQCN+" and slowly lowers his tail.\n\n"
              "He says \"Thank you for freeing me at last!  I leave now to take up "
              "my post.\"\n"
              "He says \""+TPQCN+", here is a token of my appreciation of your assistance.\"\n",TP);

  tell_object(TP,"\n%^BOLD%^As the name \"Scorpio\" is spoken, the air shimmers around "
              "the odd gargoyle.  \n"
              "The gargoyle comes to life!!\n\n"
              "SCorpio turns to you and slowly lowers his tail.\n\n"
              "He says \"Thank you for freeing me at last!  I leave now to take up "
              "my post.\"\n"
              "He says \"Here is a token of my appreciation of your assistance.\"\n");

  new(OPATH "scotoken.c")->move(TP);
  remove_item("gargoyle");
  remove_item("scorpion");
  gargoyle_gone = 1;
  return 1;
}
else {
  notify_fail("Summon who?\n");
  return 0;
}
return 1;
}
