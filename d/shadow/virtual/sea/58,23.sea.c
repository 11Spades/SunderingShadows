// sea description for Aramanth island

#include <std.h>

inherit ROOM;

int is_virtual()
{
  return 1;
}

int is_water()
{
  return 1;
}

int is_dockentrance()
{
  return 1;
}

void create()
{
  ::create();
  set_indoors(1);
     set_property("no teleport",1);
  set_light(2);
  set_short("You are on the Saakrune Sea");
  set_long("	%^BOLD%^You are on the Saakrune Sea.%^RESET%^\n"
      "You see the dock of an island here.\n");
  set_exits( ([
	       "north" : "/d/shadow/virtual/57,23.sea",
	       "south" : "/d/shadow/virtual/59,23.sea",
	       "east"  : "/d/shadow/virtual/58,24.sea",
	       "west"  : "/d/shadow/virtual/58,22.sea",
          "dock"  : "/d/shadow/virtual/sea/aramanth.dock"
		]));
	
  set_smell("default","You can smell the ocean on the beaches.");
  set_listen("default","You can hear the crashing waves to the south.");
}
		
