#include <std.h>
inherit "/d/magic/symbols/holy_symbol.c";

void create(){
    ::create();
    set_id(({"holy symbol", "lord_shadow_holy_symbol", "symbol", "medallion"}));
    set_name("holy symbol");
    set_short("holy symbol");
    set_long("This is a holy symbol.");
}
    
void init(){
    ::init();
    set_name("onyx medallion");
    set_short("%^RESET%^%^C059%^A m%^CRST%^e%^C059%^dall%^CRST%^i%^RESET%^%^C059%^on of on%^CRST%^y%^C059%^x %^RESET%^%^C075%^ins%^C081%^cri%^C075%^bed %^RESET%^%^C059%^with an %^RESET%^%^C075%^azur%^RESET%^%^C081%^e dia%^C075%^mond%^CRST%^");
    set_long("%^RESET%^%^C059%^This is a simple m%^CRST%^e%^C059%^dall%^CRST%^i%^C059%^on of on%^CRST%^y%^C059%^x strung upon a %^CRST%^silver %^RESET%^%^C059%^chain. The image of an %^RESET%^%^C075%^azur%^RESET%^%^C081%^e dia%^RESET%^%^C075%^mond %^RESET%^%^C059%^has been %^RESET%^%^C075%^ins%^C081%^cri%^C075%^bed %^RESET%^%^C059%^on each surface of the m%^CRST%^e%^C059%^dall%^CRST%^i%^C059%^on.%^CRST%^");
    
}
