#include "/d/shadow/mon/melnmarn.h"
#include <std.h>
inherit ROOM;

void create() {
  ::create();
    set_properties((["light":2, "indoors":1]));
    set("short", "Pennor's Weapon Store Storage Room");
    set("long", "Only supplies and such here.\n");
    set_exits( (["up" : ROOMDIR+"weapon"]) );
}

void reset() {

::reset();
if(!present("awlpike"))
 new(WEAPONDIR+"awlpike")->move(this_object()); 
if(!present("bardiche"))
 new(WEAPONDIR+"bardiche")->move(this_object()); 
if(!present("bastard"))
 new(WEAPONDIR+"bastard")->move(this_object()); 
if(!present("bastard_two"))
 new(WEAPONDIR+"bastard_two")->move(this_object()); 
if(!present("spear"))
   new(WEAPONDIR+"mspear")->move(this_object());
if(!present("battle axe"))
 new(WEAPONDIR+"battle_axe")->move(this_object()); 
if(!present("bec de corbin"))
 new(WEAPONDIR+"bec_de_corbin")->move(this_object()); 
if(!present("bill-guisarme"))
 new(WEAPONDIR+"bill-guisarme")->move(this_object()); 
if(!present("broad"))
 new(WEAPONDIR+"broad")->move(this_object()); 
if(!present("club"))
 new(WEAPONDIR+"club")->move(this_object()); 
if(!present("mclub"))
 new(WEAPONDIR+"mclub")->move(this_object());
if(!present("dagger"))
 new(WEAPONDIR+"dagger")->move(this_object()); 
if(!present("fauchard"))
 new(WEAPONDIR+"fauchard")->move(this_object()); 
if(!present("flail"))
 new(WEAPONDIR+"flail")->move(this_object()); 
if(!present("glaive"))
 new(WEAPONDIR+"glaive")->move(this_object()); 
if(!present("guisarme"))
 new(WEAPONDIR+"guisarme")->move(this_object()); 
if(!present("halberd"))
 new(WEAPONDIR+"halberd")->move(this_object()); 
if(!present("handaxe"))
 new(WEAPONDIR+"handaxe")->move(this_object()); 
if(!present("khopesh"))
 new(WEAPONDIR+"khopesh")->move(this_object()); 
if(!present("knife"))
 new(WEAPONDIR+"knife")->move(this_object()); 
if(!present("longsword"))
 new(WEAPONDIR+"longsword")->move(this_object()); 
if(!present("mace"))
 new(WEAPONDIR+"mace")->move(this_object()); 
if(!present("military_fork"))
 new(WEAPONDIR+"military_fork")->move(this_object()); 
if(!present("morningstar"))
 new(WEAPONDIR+"morningstar")->move(this_object()); 
if(!present("partisan"))
 new(WEAPONDIR+"partisan")->move(this_object()); 
if(!present("pick"))
 new(WEAPONDIR+"pick")->move(this_object()); 
if(!present("sickle"))
 new(WEAPONDIR+"sickle")->move(this_object()); 
if(!present("quarter_staff"))
 new(WEAPONDIR+"quarter_staff")->move(this_object()); 
if(!present("scimitar"))
 new(WEAPONDIR+"scimitar")->move(this_object()); 
if(!present("scourge"))
 new(WEAPONDIR+"scourge")->move(this_object()); 
if(!present("shortsword"))
 new(WEAPONDIR+"shortsword")->move(this_object()); 
if(!present("spetum"))
 new(WEAPONDIR+"spetum")->move(this_object()); 
if(!present("trident"))
 new(WEAPONDIR+"trident")->move(this_object()); 
if(!present("two_hand_sword"))
 new(WEAPONDIR+"two_hand_sword")->move(this_object()); 
if(!present("voulge"))
 new(WEAPONDIR+"voulge")->move(this_object()); 
if(!present("warhammer"))
 new(WEAPONDIR+"warhammer")->move(this_object()); 
if(!present("whip"))
 new(WEAPONDIR+"whip")->move(this_object()); 
}

