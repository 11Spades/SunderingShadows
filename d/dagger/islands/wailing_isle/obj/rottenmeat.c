// Chernobog & Titania (4/25/22)
// Wailing Isle - Rotten Meat

#include <std.h>

inherit "/std/food.c";

void create(){
	::create();
	set_name("putrid meat");
	set_id(({"meat","putrid meat","food"}));
	set_short("%^CRST%^%^RESET%^%^C059%^slab of %^C058%^p%^C059%^u%^C058%^t%^C064%^r%^C059%^i%^C058%^d%^RESET%^%^C059%^ meat%^CRST%^");
	set_long("%^CRST%^%^RESET%^%^C059%^This is a %^C058%^wretched chunk%^C059%^ of forgotten meat%^RESET%^%^C059%^. %^C246%^Maggots%^C059%^ burrow deep within its putrid depths and wriggle across its slimy surface. %^C243%^Feeling hungry?%^CRST%^");
	set_weight(1);
	set_value(0);
	set_destroy();
	set_poison(0);
	set_strength(3);
    set_raw(3);
	set_my_mess("%^CRST%^%^RESET%^%^C059%^EWW. It tastes even fouler than it looks.%^CRST%^");
	set_your_mess("chokes down some rotten meat. So utterly disgusting.");
}

