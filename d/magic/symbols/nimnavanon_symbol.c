#include <std.h>
inherit "/d/magic/symbols/holy_symbol.c";

void create(){
    ::create();
    set_id(({"holy symbol", "nim_holy_symbol", "symbol", "medallion", "nimnavanon_holy_symbol"}));
    set_name("holy symbol");
    set_short("holy symbol");
    set_long("This is a holy symbol.");
}
    
void init(){
    ::init();
    set_name("oak medallion");
    set_short("%^RESET%^%^C058%^A rustic %^RESET%^%^C240%^wolf paw %^RESET%^%^C058%^carving etched upon an %^RESET%^%^C094%^o%^C130%^a%^C136%^k %^RESET%^%^C130%^m%^C094%^e%^C130%^d%^C136%^a%^C130%^l%^C094%^l%^C130%^i%^C136%^o%^RESET%^%^C130%^n%^CRST%^");
    set_long("%^RESET%^%^C058%^This rustic %^RESET%^%^C240%^wolf paw %^RESET%^%^C058%^carving has been expertly etched upon an %^RESET%^%^C094%^o%^C130%^a%^C136%^k %^RESET%^%^C130%^m%^C094%^e%^C130%^d%^C136%^a%^C130%^l%^C094%^l%^C130%^i%^C136%^o%^RESET%^%^C130%^n%^RESET%^%^C058%^. The %^RESET%^%^C136%^wood %^RESET%^%^C058%^has been left %^RESET%^%^C124%^r%^C160%^a%^C124%^w%^RESET%^%^C058%^, the %^RESET%^%^C102%^bark %^RESET%^%^C058%^still clinging to the outer rim. The wooden disc hangs from a %^RESET%^%^C144%^b%^C101%^r%^C144%^a%^C102%^i%^C144%^d%^C101%^e%^RESET%^%^C144%^d leather cord%^RESET%^%^C058%^.%^CRST%^");
    
}
