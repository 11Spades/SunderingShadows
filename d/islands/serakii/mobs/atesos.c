#include <std.h>
#include <daemons.h>
#include "../serakii.h"
inherit "/std/vendor";


void create() {
   ::create();
   set_name("Atesos Brock");
   set_id(({"atesos","Atesos Brock","clerk","shop keeper","shopkeeper","brock"}));
   set_short("%^C195%^Atesos Brock, the "+
   "%^C178%^general store clerk"+
   "%^C195%^ of Serith%^CRST%^");
   set("aggressive", 0);
   set_level(19);
   set_long("%^C061%^Atesos is a %^C094%^barrel "+
   "chested%^C061%^ human in the %^C246%^middle "+
   "%^C061%^of his years. There is a start to "+
   "%^C243%^gray %^C061%^in his %^C242%^thick "+
   "black hair%^C061%^, but none of the "+
   "%^C088%^strength %^C061%^has left his "+
   "form yet. Kind blue eyes look back from "+
   "bushy almost unruly eyebrows. He wears "+
   "simple %^C094%^homespun clothes%^C061%^ "+
   "without any %^C227%^jewelry %^C061%^except "+
   "a small %^C231%^white chess rook%^C061%^ "+
   "pin on the collar of his shirt. %^CRST%^\n\n"+
        "<help shop> will get you a list of "+
		"shop commands.\n");
   set_gender("male");
   set_alignment(6);
   set_race("human");
   add_money("gold", random(500));
   set_body_type("human");
   set_property("no attack", 1);
   set_hd(19,3);
   set_max_hp(query_hp());
   set_max_sp(query_hp());
   set_sp(query_max_sp());
   set_mp(random(500));
   set_max_mp(query_mp());
   set_storage_room(STORAGE"gs_storage.c");
   set_exp(0);
   remove_std_db();
}
