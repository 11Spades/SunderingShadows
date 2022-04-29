// Chernobog & Titania (4/25/22)
// Wailing Isle - Apple

#include <std.h>

inherit "/std/food.c";

void create(){
	::create();
	set_name("apple");
	set_id(({"apple","small apple","food"}));
	set_short("%^RESET%^%^CRST%^%^C124%^s%^C131%^m%^C125%^a%^C124%^ll a%^C125%^p%^C131%^p%^C124%^le%^CRST%^");
	set_long("%^RESET%^%^CRST%^%^C124%^It's a bit %^C058%^b%^C130%^r%^C196%^uis%^C130%^e%^C058%^d%^RESET%^%^C124%^ and %^C058%^w%^C130%^r%^C196%^inkl%^C130%^e%^C058%^d%^RESET%^%^C124%^, but probably edible if you are hungry.%^CRST%^");
	set_weight(1);
	set_value(0);
	set_destroy();
	set_poison(0);
	set_strength(1);
	set_my_mess("%^RESET%^%^CRST%^%%^C247%^You choke down the grainy bites of apple.%^CRST%^");
	set_your_mess("finishes the small apple in a couple of bites.");
}

