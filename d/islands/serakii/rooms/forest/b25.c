#include <std.h>
#include "../../serakii.h"

inherit STORAGE"corrupted_forest.c";

void create(){
   ::create();

set_exits(([
"west" : FOR"b24",
//"hole" : somewhere,

]));

	add_item("pit","%^C060%^The %^C242%^pit%^C060%^ here seems endless. The %^C065%^trees%^C060%^ are dead all around it and even though it seems endless and bottomless %^C056%^miasma%^C060%^ seems to flow out of it. There is no way you can see to enter it.%^CRST%^");

    set_long(::query_long()+"\n%^C245%^The %^C066%^forest%^C245%^ has been wrecked here by what looks like an %^C059%^endless pit%^C245%^.%^CRST%^\n");
}
