// sea description for Shadow dock

#include <std.h>

inherit ROOM;

int is_virtual() { return 1; }
int is_water() { return 1; }
int is_dockentrance() { return 1; }

void create() {
    set_indoors(1);
    ::create();
    set_light(2);
    set_short("You are on the Saakrune Sea");
     set_property("no teleport",1);
    set_long(
@OLI
	%^BOLD%^You are on the Saakrune Sea.%^RESET%^
You see the dock leading to shadow here.
OLI
	);
	set_exits(([
		"north":"/d/shadow/virtual/35,0.sea",
		"south":"/d/shadow/virtual/37,0.sea",
		"east":"/d/shadow/virtual/36,1.sea",
		"dock":"/d/shadow/virtual/sea/shadow.dock"
		]));
	
	set_smell("default","You can smell the arid desert air blowing from the west.");
	set_listen("default","You can hear the crashing waves to the east.");
}
		
