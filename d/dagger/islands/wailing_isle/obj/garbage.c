// Chernobog & Titania (2/24/22)
// Wailing Isle - Garbage

#include <std.h>

inherit OBJECT;

void create(){
    ::create();
    set_name("garbage");
    random_trash();
    set_weight(3);
    set_value(0);
}

void random_trash(){
    switch(random(5)){
        case 0 :
            set_id(({"garbage", "hat", "waterlogged hat"}));
            set_short("%^CRST%^%^RESET%^%^C100%^old %^C094%^wa%^C107%^te%^C101%^rl%^C100%^og%^C094%^ge%^C107%^d%^RESET%^%^C100%^ hat%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C100%^This %^C094%^hat%^C100%^ is %^C101%^soaked%^C100%^ and %^C101%^frayed%^C100%^. It would probably fall apart if you tried to wear it.%^CRST%^");
            break;
        case 1 :
            set_id(({"garbage", "driftwood", "wood"}));
            set_short("%^CRST%^%^RESET%^%^C100%^d%^C101%^rif%^C100%^tw%^C101%^oo%^C100%^d%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C101%^Just some soaked bits of %^C100%^wood%^C101%^.%^CRST%^");
            break;
        case 2 :
            set_id(({"garbage", "rigging"}));
            set_short("%^CRST%^%^RESET%^%^C101%^r%^C247%^u%^C243%^i%^C101%^n%^C247%^ed ri%^C101%^g%^C243%^gi%^C247%^n%^C101%^g%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C247%^This bit of %^C244%^old rigging%^C247%^ is too far past its prime to be useful.%^CRST%^");
            break;
        case 3 :
            set_id(({"garbage", "bottle", "broken bottle"}));
            set_short("%^CRST%^%^RESET%^%^C100%^br%^C106%^ok%^C107%^en bo%^C106%^tt%^C100%^le%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C106%^The %^C100%^rum%^C106%^ is gone and the glass is %^C107%^cracked%^C106%^. It is completely useless.%^CRST%^");
            break;
        case 4 :
            set_id(({"garbage", "doll", "tattered doll"}));
            set_short("%^CRST%^%^RESET%^%^C182%^t%^C188%^a%^C182%^tt%^C188%^e%^C182%^re%^C188%^d %^C182%^doll%^CRST%^");
            set_long("%^CRST%^%^RESET%^%^C182%^This r%^C188%^a%^C182%^gg%^C188%^e%^C182%^d, w%^C188%^%^C189%^at%^C182%^e%^C188%^rlo%^C189%^g%^C188%^ge%^RESET%^%^C182%^d %^C188%^doll%^C182%^ was once some child's %^C188%^prized%^C182%^ possession.%^CRST%^");
            break;
    }
    return;
}

