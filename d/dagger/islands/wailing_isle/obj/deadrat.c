// Chernobog & Titania (4/25/22)
// Wailing Isle - Dead Rat

#include <std.h>

inherit "/std/food.c";

void create(){
	::create();
	set_name("dead rat");
	set_id(({"rat","dead rat","food"}));
	set_short("%^RESET%^%^CRST%^%^C058%^%^C059%^de%^C058%^a%^C059%^d %^C058%^rat%^CRST%^");
	set_long("%^RESET%^%^CRST%^%^C058%^What at first glance seemed to be a rough leather pouch is actually the %^C064%^w%^C058%^i%^C059%^t%^C064%^h%^C058%^e%^C059%^r%^C064%^e%^C058%^d %^C064%^b%^C058%^o%^C059%^d%^C064%^y%^RESET%^%^C058%^ of a long-dead rat. A jaw of %^C059%^prickly teeth%^C058%^, a %^C059%^long wiry tail%^C058%^, and a few %^C059%^tufts%^C058%^ of %^C059%^hair%^C058%^ all that's left to identify it.%^CRST%^");
	set_weight(1);
	set_value(0);
	set_destroy();
	set_poison(0);
	set_strength(3);
    set_raw(3);
	set_my_mess("%^RESET%^%^CRST%^%^C059%^What sort of monster are you? Eww!%^CRST%^");
	set_your_mess("just devoured a leathery old rat corpse. Gag!");
}

