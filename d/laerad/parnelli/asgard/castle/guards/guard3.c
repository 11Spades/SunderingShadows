//Coded by Bane//
#include <std.h>
#include <daemons.h>
#include "/d/laerad/parnelli/asgard/castle/daemon/bane.h"
inherit MONSTER;
object *attackers;
object ob;
void create(){
    ::create();
    set_id(({"guard","royal bodyguard","bodyguard"}));
    set_name("royal bodyguard");
    set_short("A royal bodyguard");
    set_long(
	"This is one of the kings special bodyguards.  He is a short "+
	"stocky fellow, and he looks as old as the castle itself.  "+
	"Although he wouldnt be the King's bodyguard if he couldnt "+
	"hold his own."
    );
    set_body_type("human");
    set_race("dwarf");
    set_gender("male");
    set_size(1);
    set_hd(22+random(10),5);
    set_hp(query_hd()*10);
    set_property("magic resistance",35);
    set_property("swarm",1);
    set_property("full attacks",1);
    set_overall_ac(-2);
    set_exp(10000);
    set_stats("strength",19);
    set_stats("constitution",18);
    set_stats("dexterity",17);
    set_stats("charisma",17);
    set_damage_bonus(5);
    set_class("fighter");
    set_guild_level("fighter",query_hd());
    add_search_path("/cmds/fighter");
    set_alignment(1);
    add_money("gold",random(500)+150);
    add_money("platinum",random(10)+5);
    set_wielding_limbs(({"right hand","left hand"}));
    ob = new("/d/shadow/obj/armor/chain");
    ob->move(TO);
    ob->set_property("enchantment",4);
    if(random(10)) ob->set_property("monsterweapon",1);
    command("wear armor");
    ob = new("/d/shadow/obj/armor/helm");
    ob->move(TO);
    ob->set_property("enchantment",2);
    if(random(10)) ob->set_property("monsterweapon",1);
    command("wear helm");
    ob = new("/d/shadow/obj/weapon/longsword");
    ob->move(TO);
    ob->set_property("enchantment",4);
    if(random(10)) ob->set_property("monsterweapon",1);
    command("wield sword in right hand and left hand");
}
void init(){
    ::init();
    if(wizardp(TP)) return 1;
        if((string)TP->query_race() == "human" || (string)TP->query_race() == "elf"
|| (string)TP->query_race() == "half-elf" || (string)TP->query_race() ==
"dwarf" || (string)TP->query_race() == "gnome" || (string)TP->query_race() ==
"halfling" || (string)TP->query_race() == "horse"){
	    return 1;
	}
   force_me("kill "+TPQN);
	return 1;
}
void heart_beat(){
        int i, j;
        object *att;
        ::heart_beat();
        if((att = (object *)TO->query_attackers()) != ({})){
                j = sizeof(att);
                for(i = 0;i <j;i++){
                        call_out("force_me",2,"rush "+att[i]->query_name());

                }
	if(OVER->query_alarm() == 0) OVER->sound_alarm(ETO);
    }
}
