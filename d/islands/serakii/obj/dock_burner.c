
//Incense Docks
#include <std.h>
#include "../serakii.h"

inherit OBJ("burner.c");

//Inherit the right theater
#include "/realms/loki/theater/serakii/dock.h"

void create() {
    ::create();
    set_name("dock incense burner");
    set_id(({"incense","burning incense","incense burner","burner","wood framed incense burner"}));
    set_weight(1000000);
set_short("%^C094%^wo%^C058%^o%^C094%^d fram%^C095%^e%^C094%^d i%^C246%^n%^C094%^cen%^C246%^s%^C094%^e b%^C124%^u%^C094%^rn%^C196%^e%^C094%^r%^CRST%^");
set_long("%^C094%^This %^C244%^metal bowl%^C094%^ filled with incense has been framed up in a simple %^C058%^wooden box%^C094%^. The %^C059%^wood%^C094%^ itself looks like it is reclaimed from a %^C142%^ship%^C094%^ as there are %^C251%^barnacles%^C094%^ and %^C029%^discoloration%^C094%^ from being in %^C044%^water%^C094%^ for some time. There is a pile of %^C222%^incense%^C094%^ that has been set alight, and smoke drifts up from it slowly. You could %^C226%^inhale%^C094%^ the incense to see what it smells like.\n%^CRST%^");
    set_value(0);
    set_property("no animate",1);
}
