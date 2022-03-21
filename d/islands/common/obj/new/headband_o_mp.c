#include <std.h>
inherit "/d/common/obj/jewelry/circlet.c";

void create()
{
    ::create();
    set_name("circlet of mental prowess");
    set_id(({ "circlet", "silver circlet", "mental circlet", "circlet of mental prowess" }));
    set_short("%^BOLD%^%^WHITE%^Circlet of %^CYAN%^M%^BLUE%^e%^CYAN%^nt%^BLUE%^a%^CYAN%^l Pr%^BLUE%^o%^CYAN%^w%^BLUE%^e%^CYAN%^ss%^RESET%^");
    set_obvious_short("%^BOLD%^%^WHITE%^s%^RESET%^i%^BOLD%^lv%^RESET%^e%^BOLD%^r circlet adorned with a %^BOLD%^%^BLUE%^bl%^RESET%^%^BLUE%^u%^BOLD%^%^BLUE%^e g%^RESET%^%^BLUE%^e%^BOLD%^%^BLUE%^m%^RESET%^");
    set_long("%^BOLD%^%^WHITE%^This simple s%^RESET%^i%^BOLD%^lv%^RESET%^e%^BOLD%^r circlet has a small %^BOLD%^%^BLUE%^bl%^RESET%^%^BLUE%^u%^BOLD%^%^BLUE%^e g%^RESET%^%^BLUE%^e%^BOLD%^%^BLUE%^m %^WHITE%^set so that when worn, the gemstone perches on the wearer's brow as a symbol the powerful inner eye.  Despite its simplicity, the circlet has obviously been wrought by the hand of a master jeweler.%^RESET%^");
    set_lore("%^BOLD%^%^WHITE%^These circlets of mental prowess were once a common sight upon the brows of the realm's spellcasters, but those crafted lately are merely pale imitations.  It is rumored that an even more powerful version, referred to as circlets of mental superiority, once existed.  However, no examples of it have been seen in over three thousand years.%^RESET%^");
    set_value(400000);
    set_property("lore difficulty", 0);
    set_size(-1);
    set_property("enchantment", 7);
    set_wear((: TO, "wear_func" :));
    set_remove((: TO, "remove_func" :));
    set_item_bonus("intelligence", 6);
    set_item_bonus("wisdom", 6);
    set_item_bonus("will", 6);
	set_property("quest required", "%^BOLD%^%^RED%^Defeated the great red wyrm Klauth!%^RESET%^");
	set_property("level required", 35);
}

int wear_func(){
    object player, room;
    player = environment(this_object());
    room = environment(player);
    
    tell_object(player, "%^RESET%^%^BOLD%^The %^BLUE%^gem %^WHITE%^on the "+query_obvious_short()+" begins to softly %^CYAN%^glow %^WHITE%^as you place it upon your brow.%^RESET%^");
    tell_room(room, "%^RESET%^%^BOLD%^The %^BLUE%^gem %^WHITE%^on "+player->query_cap_name()+"%^RESET%^%^BOLD%^'s "+query_obvious_short()+" begins to %^CYAN%^glow %^WHITE%^as "+player->query_subjective()+" places it upon "+player->query_possessive()+" brow.%^RESET%^", player);
    return 1;
}

int remove_func(){
    object player, room;
    player = environment(this_object());
    room = environment(player);
    
    tell_object(ETO, "%^RESET%^%^BOLD%^The %^BLUE%^gem %^WHITE%^on the "+query_obvious_short()+" stops %^CYAN%^glowing %^WHITE%^as you remove it from your brow.%^RESET%^");
    tell_room(EETO, "%^RESET%^%^BOLD%^The %^BLUE%^gem %^WHITE%^on "+player->query_cap_name()+"%^RESET%^%^BOLD%^'s "+query_obvious_short()+" stops %^CYAN%^glowing %^WHITE%^as "+player->query_subjective()+" removes it from "+player->query_possessive()+" brow.%^RESET%^", player);
    return 1;
}

