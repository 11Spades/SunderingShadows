#include <std.h>

inherit "/std/vendor";

create() {
    ::create();
    set_name("Naccoom");
    set_id( ({"trader", "naccoom", "Naccoom"}) );
    set_short("Naccoom the trader");
    set("aggressive", 0);
    set_level(1);
    set_long(
      "   Naccoom is withered from his travels, standing bent and weak before you. He can sell you what you want, but because he is all that's left of those who collected these rare items that is how it stands."
    );
    set_gender("male");
    set_alignment(4);
    set("race", "human");
    set_body_type("human");
    set_storage_room("/d/islands/tonerra/spec_stor.c");
    set_hd(1,1);
    set_exp(10);
    set_items_allowed("misc");
    set_max_hp(20);
    set_hp(20);
}
