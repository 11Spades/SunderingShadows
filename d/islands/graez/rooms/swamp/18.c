
#include <std.h>
#include "../../graez.h"

inherit STORAGE"swamp.c";



void create(){
    ::create();
    set_long(::query_long()+"\n%^CRST%^Toward the east, the ground begins to ascend, a path leading up out of the swamp and through the %^RESET%^%^C058%^foothills %^CRST%^where the massive %^RESET%^%^C246%^z%^C248%^i%^C246%^g%^C244%^g%^RESET%^%^C246%^u%^RESET%^%^C248%^r%^RESET%^%^C250%^a%^RESET%^%^C246%^t %^RESET%^of %^RESET%^%^C241%^Nurval%^CRST%^ can be seen, the skies preternaturally %^RESET%^%^C240%^dark %^RESET%^within its proximity.%^CRST%^\n");
    set_exits(([
        "northwest" : SWAM"17",
        "east" : "/d/islands/graez/nurval/room/path1",
        ]));
}

void reset()
{
    ::reset();
    if (!present("guard"))
        new("/d/dagger/nurval/mon/necroknight")->move(TO);
    if (!present("guard 2"))
        new("/d/dagger/nurval/mon/necroknight")->move(TO);
    if (!present("guard 3"))
        new("/d/dagger/nurval/mon/necroknight")->move(TO);
    if (!present("banshee"))
        new("/d/dagger/nurval/mon/banshee")->move(TO);
    if (!present("banshee 2"))
        new("/d/dagger/nurval/mon/banshee")->move(TO);
    if (!present("bonewyvern"))
        new("/d/dagger/nurval/mon/bonewyvern")->move(TO);
}

