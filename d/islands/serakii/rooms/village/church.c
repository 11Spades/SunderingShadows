


#include <std.h>
#include "../../serakii.h"

inherit "/std/church";

void create(){
   ::create();
    set_light(2);
    set_indoors(1);
    set_name("a cozy church");
	set_short("a%^C094%^ c%^C243%^o%^C094%^zy ch%^C243%^u%^C094%^r%^C243%^c%^C094%^h%^CRST%^");
    set_long("%^C060%^This small church is just large enough to serve a small community. %^C094%^Six benches%^C060%^ serve as pews for the faithful and all are arranged to face a small %^C243%^stone altar%^C060%^ at the head of the church. %^C094%^Wood rafters%^C060%^ hold up the roof and a %^C241%^single iron chandelier%^C060%^ %^C227%^lights %^C060%^the room.%^CRST%^\n");
   set_exits(([
		  "north" : TOWN"14",



   ]));

}


