#include <std.h>
#include "/d/dagger/marsh/tower/short.h"
inherit TROOM;

void create() {
    ::create();
    set_property("light",0);
    set_property("indoors",1);
    set_property("no teleport",1);
    set_long("%^RED%^"
	"The small and narrow hallway is made of the same %^BOLD%^"
	"blood-red%^RESET%^%^RED%^ stone as seen in other parts of the tower. "
	"The stone calls out to you as though it is alive and held captive in "
	"an endless state of torment. This part of the hallway is decorated "
	"only by splashes of blood, long dried, on the floor."
	"%^RESET%^"
    ); 
    set_short("%^RED%^Tower Hallway%^RESET%^");
    set_listen("default",
        "It is dead silent, as though sound itself fears to roam here."
    );
    set_smell("default",
        "You smell the decaying blood splattered about the room."
    );
    set_items(([
	"stone":"%^RED%^The stone used to form the chamber is made from an unknown "
	"material and seems to glow in it's blood-red colour. As you gaze upon it, "
	"you hear the distant laughter of Grazzt.%^RESET%^",
	"blood":"%^RED%^The blood seems to have been here for many years "
	"and its origin is a mystery.",
    ]));
    set_exits(([
        "north": RPATH "a7",
        "south": RPATH "a1",
    ]));

    set_pre_exit_functions(({"south"}),({"exitb_fun"}));
    set_pre_exit_functions(({"north"}),({"exita_fun"}));
}
int exita_fun() {
    if(present("reaver")) {
        write("The reaver blocks your way!");
        return 0;
    }
    write("%^GREEN%^As you head to the north, you hear a faint *click* beneath "
	"your feet.%^RESET%^"
    );
    return 1;
}
int exitb_fun() {
    if(present("reaver")) {
        write("The reaver blocks your way!");
        return 0;
    }
    return 1;
}
void reset() {
    ::reset();
    if(!present("reaver")) {
        new( MPATH "reaver3.c" )->move(TO);
    }
}
