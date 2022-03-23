#include <std.h>
inherit "/std/food.c";

void create()
{
        ::create();
        set_name("fresh baked bread");
        set_short("%^C094%^fresh baked bread%^RESET%^");
        set_id(({"food","serith_market", "bread", "fresh baked bread", "baked bread"}));
        set_long("this loaf of %^C058%^bread%^CRST%^ was baked today. It is a simple peasant bread baked into a circular loaf. Normally the %^C058%^bread%^CRST%^ is either pulled apart and eaten or cut to make a trencher.");
        set_weight(1);
        set_value(25);
        set_destroy();
        set_poison(0);
        set_strength(25);
        set_my_mess("%^C094%^You tear into the fresh baked bread.%^CRST%^");
        set_your_mess("%^C094%^tears into the bread and eats the whole loaf.%^CRST%^");
}
