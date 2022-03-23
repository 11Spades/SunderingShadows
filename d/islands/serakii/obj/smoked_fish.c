#include <std.h>
inherit "/std/food.c";

void create()
{
        ::create();
        set_name("smoked fish");
        set_short("%^C244%^smo%^C136%^k%^C244%^ed f%^C136%^is%^C244%^h%^CRST%^");
        set_id(({"food","serith_market", "fish", "smoked fish","cod","smoked cod"}));
        set_long("This single %^C243%^cod%^CRST%^ has been scaled and %^C130%^smoked%^CRST%^ for some time, allowing it to be stored for a long time and eaten without further cooking");
        set_weight(1);
        set_value(40);
        set_destroy();
        set_poison(0);
        set_strength(40);
        set_my_mess("%^C246%^You eat the fish, savoring the %^C136%^smokey%^C246%^ flavor%^CRST%^");
        set_your_mess("%^C245%^carefully eats the smoked cod%^CRST%^");
}
