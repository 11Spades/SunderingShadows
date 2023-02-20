// Chernobog & Titania (4/25/22)
// Wailing Isle - Orange

#include <std.h>

inherit "/std/food.c";

void create(){
	::create();
	set_name("orange");
	set_id(({"orange","plump orange","food"}));
	set_short("%^CRST%^%^RESET%^%^C166%^plu%^C167%^m%^C166%^p oran%^C167%^g%^C166%^e%^CRST%^");
	set_long("%^CRST%^%^RESET%^%^C166%^A bit of %^C106%^m%^C113%^o%^C106%^ld%^RESET%^%^C166%^ has begun to consume the orange's peel, but the inside is still perfectly edible and juicy... probably.%^CRST%^");
	set_weight(1);
	set_value(0);
	set_destroy();
	set_poison(0);
	set_strength(1);
	set_my_mess("%^CRST%^%^RESET%^%^C106%^You enjoy the juicy orange.%^CRST%^");
	set_your_mess("finishes the last of the orange.");
}

