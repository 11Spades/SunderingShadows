//Coded by Bane//
// modified slightly to recharge while it's not in use
#include <std.h>
inherit "/d/common/obj/jewelry/ring.c";
int uses;

void create()
{
    ::create();
    set_id(({"ring","ring of regeneration","regen ring"}));
    set_name("Ring of Regeneration");
    set_obvious_short("%^BOLD%^%^GREEN%^An emerald ring%^RESET%^");
    set_short("%^BOLD%^%^GREEN%^A ring of regeneration%^RESET%^");
    set("lore",
	"This is a beautiful emerald ring.  It is known to most as a "+
	"ring of regeneration.  Wear this powerful ring and you will heal "+
	"at a phenomenal rate." );
    set_long("%^RESET%^%^BOLD%^%^YELLOW%^This ring has been created with remarkable craftsmanship.  Intricate "
		"runes are carved into a pure gold band that rises just high enough to encircle the edges of a large, "
		"square cut %^RESET%^%^BOLD%^%^GREEN%^emerald.%^RESET%^%^BOLD%^%^YELLOW%^  The ring is so well crafted "
		"that the %^RESET%^%^BOLD%^%^GREEN%^emerald%^RESET%^%^BOLD%^%^YELLOW%^ almost seems to be an extension "
		"of its golden band.%^RESET%^");
	//set_long("This is a beautiful golden ring that has a large rectangularly cut emerald set in the very center of it.");
    set_value(7000);
    set_wear((:TO,"wer_me":));
    set_remove((:TO,"remov_me":));
    set_heart_beat(6);
    uses = 0;
}
void wer_me()
{
    tell_object(ETO,"Your skin begins to tingle and revitalize.");
    ETO->set_property("fast healing", 1);
    return 1;
}
void remov_me(){
    tell_object(ETO,"Your skin begins feels dry and normal again.");
    ETO->set_property("fast healing", -1);
    return 1;
}
