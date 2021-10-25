// Chernobog (10/25/21)
// Spell Focus - Mithral Dagger

#include <std.h>

inherit "/d/common/obj/weapon/dagger.c";

void create(){
    ::create();
    set_name("mithral dagger");
    set_id(({"dagger","mithral dagger"}));
    set_short("%^RESET%^%^CRST%^%^C244%^A short %^C189%^mi%^C195%^t%^C189%^h%^C195%^ra%^C189%^l %^C250%^dagger %^C244%^covered in %^C039%^r%^C045%^u%^C051%^n%^C039%^e%^C045%^s%^CRST%^");
    set_long("%^RESET%^%^CRST%^%^C244%^Intricate %^C039%^r%^C045%^u%^C051%^n%^C039%^e%^C045%^s %^C244%^run the length of this %^C250%^short dagger%^C244%^, crafted from %^C189%^g%^C195%^l%^C189%^im%^C195%^me%^C189%^r%^C195%^i%^C189%^ng %^C195%^mi%^C189%^t%^C195%^h%^C189%^ri%^C195%^l%^RESET%^%^C244%^. It lacks a proper crosspiece, and the grip has been wound in loops of %^C136%^le%^C130%^a%^C136%^th%^C130%^e%^C136%^r c%^C130%^o%^C136%^rd %^C244%^to offer some traction. The pommel flares out in four tines, curling inward on themselves to hold a precious gemstone: a %^C196%^ru%^C198%^b%^C196%^y%^C244%^, carefully cut and smoothed into a perfect sphere.%^CRST%^");
    
    set_lore("%^RESET%^%^CYAN%^The runes running along the length of the dagger are precise and specific, as is the the gemstone set in the pommel. They allow these blades to be used as a magical focus that some arcane spell casters can use to create a protective wreath of blades about themselves.%^RESET%^");
    set_property("lore", 20);
    
    set_value(50000);
}

