// sea description for Deku island

#include <std.h>

inherit ROOM;

int is_virtual() { return 1; }
int is_water() { return 1; }
int is_dockentrance() { return 1; }

void create() {
    set_indoors(1);
    ::create();
    set_light(2);
    set_short("You are in the Desert");
    set_long(
@OLI
	%^BOLD%^You are on the Saakrune Sea.%^RESET%^
You see an island in the water here.
OLI
	);
	set_exits(([
		"north":"/d/shadow/virtual/15,8.sea",
		"south":"/d/shadow/virtual/17,8.sea",
		"east":"/d/shadow/virtual/16,9.sea",
		"west":"/d/shadow/virtual/16,7.sea",
		"dock":"/d/shadow/virtual/sea/undead.dock"
		]));
	
	set_smell("default","You can smell the arid desert air blowing from the west.");
	set_listen("default","You can hear the crashing waves to the east.");
}
		
