#include <std.h>
#include "../tharis.h"
inherit "/std/identifier";
//inherit VENDOR;
//inherit "/std/spell_vend.c";

void create() {
    ::create();
    set_gender("male");
    set_name("Azakoth Mor'Geran, Tharis city wizard");
    set_race("ogre-mage");
    set_alignment(5);
    set_class("mage");
    set_mlevel("mage",16 + random(3));
    set_guild_level("mage",query_level());
    set_hp(query_level() * 6 + random(21));
    set_exp(query_max_hp() * 8);
    set_stats("intelligence",22);
    set_stats("strength",16);
    set_stats("charisma",18);
    set_stats("wisdom",14);
    set_stats("dexterity",12);
    set_stats("constitution",16);
    set_spells(({"lightning bolt","burning hands","scorcher","magic missile","powerword stun"}));
    //set_spells_sold(gen_spells_sold(20));
    set_spell_chance(90);
    set_id_uses(3);
    set_detect_uses(4);
    set_highmod(4);
    set_id(({ "azakoth", "wizard"}));
    set_short("%^RESET%^%^C063%^Azakoth Mor'Geran%^RESET%^%^C061%^, %^RESET%^%^C241%^Tharis %^RESET%^%^C061%^city %^RESET%^%^C024%^w%^C031%^i%^C038%^z%^C045%^a%^C031%^r%^C024%^d%^CRST%^");
    set_long("%^RESET%^%^C061%^This massive %^RESET%^%^C063%^ogre-mage %^RESET%^%^C061%^towers over most other inhabitants of the bazaar, even while sitting at his oversized booth %^RESET%^%^C061%^surrounded by shelves of %^RESET%^%^C144%^scrolls %^RESET%^%^C061%^and %^RESET%^%^C094%^wands%^RESET%^%^C061%^. Tall %^RESET%^%^C241%^b%^C242%^l%^C243%^a%^C242%^c%^C241%^k h%^RESET%^%^C242%^o%^C243%^r%^C242%^n%^C241%^s %^RESET%^%^C061%^curl from his forehead and thick %^RESET%^%^C240%^raven-black hair %^RESET%^%^C061%^cascades down his back bound with bands of %^RESET%^%^C220%^g%^C226%^o%^RESET%^%^C227%^l%^RESET%^%^C220%^d %^RESET%^%^C061%^and %^RESET%^%^C251%^s%^C252%^i%^C253%^l%^C254%^v%^C252%^e%^C251%^r%^RESET%^%^C061%^. His %^RESET%^%^C087%^a%^C123%^z%^C159%^u%^C123%^r%^RESET%^%^C087%^e e%^RESET%^%^C123%^y%^C159%^e%^RESET%^%^C087%^s %^RESET%^%^C051%^burn %^RESET%^%^C061%^with an %^RESET%^%^C033%^a%^C039%^r%^C045%^c%^C051%^a%^C039%^n%^C033%^e l%^RESET%^%^C045%^i%^C051%^g%^C045%^h%^C033%^t %^RESET%^%^C061%^and his relatively fine-featured face is interrupted by long %^RESET%^%^C230%^tusks %^RESET%^%^C061%^that jut from his lower jaw. Rich robes of %^RESET%^%^C220%^g%^C226%^o%^C227%^l%^C220%^d %^RESET%^%^C061%^and %^RESET%^%^C241%^black %^RESET%^%^C061%^do little to hide the shape of his broad %^RESET%^%^C062%^muscular body %^RESET%^%^C061%^as he flips through a tome far too small for him, %^RESET%^%^C087%^peering %^RESET%^%^C061%^at it through a %^RESET%^%^C220%^m%^RESET%^%^C226%^o%^C227%^n%^C228%^o%^C227%^c%^C226%^l%^RESET%^%^C220%^e %^RESET%^%^C061%^as he waits for his next customer.%^CRST%^"); 
}