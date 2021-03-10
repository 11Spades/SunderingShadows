
#include <std.h>

#include "/d/stella/short.h"

inherit ROOM;

void init(){
	::init();
       	if (interactive(TP)) {
	  do_random_encounters(({MPATH"mund.c"}),5,1);
	  do_random_encounters(({OPATH"nova.c"}),5,1);
       	}
	}

void create(){
      ::create();
      set_name("Star Maze");
      set_short("%^MAGENTA%^Star Maze");
      set_terrain(BUILT_CAVE);
      set_travel(FRESH_BLAZE);
      set_property("indoors",1);
      set_property("light",1);
      set_long(
	     "%^MAGENTA%^You are in a starry maze.  You are surrounded by deep darkness.  "
	     "The only light comes from millions of tiny stars which surround "
	     "you on all sides.  As your eyes adapt to the dark, you notice "
	     "faint shimmering MAGENTA lines leading off into the darkness.  "
       );
      set_listen("default",
        "You hear nothing ... a complete absence of any sound. "
      );
      set_smell("default",
        "You smell nothing!"
      );
      set_items(([
        "stars":"There are millions of shimmering stars in every direction.  ",
        "lines":"You occasionally see a faint line heading off in some direction.  "
        "This is your only source of orientation."
       ]));
      set_exits(([
         "west": MAZEPATH "leo7",
         "southeast": MAZEPATH "leo9"
       ]));
}
