//legion soldier - LoKi

#include <std.h>
#include "../serakii.h"

inherit MONSTER;

void make_me();

void create(){
   ::create();
   set_name("legion soldier");
   set_id(({"legion","legion soldier","soldier","legion militia"}));
   set_short("soldier");
   set_long("%^C249%^Dressed in a %^C231%^pure white cassock%^C249%^, "+
   "this %^C248%^soldier %^C249%^in front of you is geared for "+
   "%^C088%^battle%^C249%^, yet stands with an almost %^C079%^"+
   "casual confidence%^C249%^. His %^C248%^armour %^C249%^is "+
   "well cared for and gleaming. His clothing is mostly "+
   "%^C231%^white%^C249%^, with a hint of %^C111%^blue "+
   "%^C249%^with different items. On most of his %^C094%^"+
   "equipment %^C249%^you see an insignia of a %^C231%^White "+
   "Sphere%^C249%^ over a %^C241%^Shield%^C249%^, signifying "+
   "this is an soldier of the Legion of Pearl.\n%^CRST%^");
   set_hd(25,12);

   set_exp(1400);
   set_stats("strength",18);
   set_stats("dexterity",18);
   set_stats("wisdom",18);
   set_stats("intelligence",18);
   set_alignment(3);
   set_size(2);
   set_body_type("human");
   add_limb("neck","neck",0,0,0);
   set_wielding_limbs(({"right hand","left hand"}));
   set_gender("male");
   set("aggressive",6);
   set_property("swarm",1);
   set_property("magic resistance",40);
   make_me();
   add_money("gold",3000+random(5));
   add_money("silver",5000+random(5));
   add_money("electrum",3000+random(5));
   set_property("no random treasure", 1);
   set_property("not random monster", 1);
   set_new_exp(35, "normal");
   set_speed(20);

}

void make_me(){
        object ob;
        int i,j,k;
        string theclass,race;
        i = random(5);
        switch(i){
        case 0: race = "%^C125%^elf%^CRST%^";
                break;
        case 1: race = "%^C125%^human%^CRST%^";
                break;
        case 2: race = "%^C125%^half-elf%^CRST%^";
                break;
        case 3: race = "%^C125%^dwarf%^CRST%^";
                break;
        case 4: race = "%^C125%^human%^CRST%^";
                break;
        }

        set_race(race);

    set_short("%^C111%^A " +query_race()+ "%^C111%^%^C111%^ "+
	"Legi%^C247%^o%^C111%^n of P%^C245%^e%^C111%^arl %^C111%^s"+
	"o%^C245%^l%^C111%^di%^C245%^e%^C111%^r%^CRST%^");
        i = random(4);
        switch(i){
        case 0..1: theclass = "fighter";
                break;
        case 2: theclass = "cleric";
                break;
        case 3: theclass = "mage";
        }
        set_class(theclass);
       set_guild_level(theclass,30);
       set_mlevel(theclass,30);

        switch(theclass){
        case "fighter":
            set_hp(1000);
            set_func_chance(80);
            set_property("full attacks",1);
            ob = new("/d/common/obj/weapon/longsword");
            ob->set_property("enchantment",5);
            ob->set_property("monsterweapon",1);
            ob->move(TO);
            command("wield sword in right hand");
            ob = new("/d/common/obj/armour/chain");
                        ob->set_property("monsterweapon",1);
            ob->move(TO);
            command("wear armor");
            ob = new(OBJ"legion_cassock.c");
                        ob->move(TO);
                        command("wear cassock");
            ob->set_property("monsterweapon",1);
                set_monster_feats(({
                    "weapon focus",
                    "expertise",
                    "knockdown",
                    "powerattack",
                    "shatter",
                    "sunder",
                    "rush",
                }));

                set_funcs(({
                    "rushit",
                    "flashit",
                    "kdit",
                }));

                break;
        case "cleric":
            set_hp(1000);
            ob = new("/d/common/obj/weapon/mace");
            ob->set_property("enchantment",5);
            ob->set_property("monsterweapon",1);
            ob->move(TO);
            command("wield mace in right hand");
            ob = new("/d/common/obj/armour/chain");
                        ob->set_property("monsterweapon",1);
            ob->move(TO);
            command("wear armor");
            command("wear armor");
            ob = new(OBJ"legion_cassock.c");
                        ob->move(TO);
                        command("wear cassock");
            ob->set_property("monsterweapon",1);
                        set_spells(({
                                "umbral strike",
                                "call lightning",
                                "harm",
                                "phantasmal killer"
                                }));
                set_spell_chance(80);
                break;
        case "mage":
                set_hp(1000);
                 new("/d/common/obj/armour/bracers")->move(TO);
                command("wear bracers");
            command("wear armor");
            ob = new(OBJ"legion_cassock.c");
                        ob->move(TO);
                        command("wear cassock");
            ob->set_property("monsterweapon",1);
                set_monster_feats(({
                    "perfect caster",
                    "spell penetration",
                    "spell power",
                }));
                    set_spells(({
                                        "magic missile",
                    "meteor swarm",
                    "magic missile",
                    "dispel magic"
                                }));
                set_spell_chance(90);
                break;
       }
}

void rushit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("rush "+targ->query_name());
}


void kdit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("knockdown "+targ->query_name());
}

void flashit(object targ){
   if(!objectp(targ)) return;
   if(!objectp(TO)) return;
   TO->force_me("flash "+targ->query_name());
}


void init()
{
    ::init();
    if (!interactive(TP)) {
        return;
    }
    if ((mixed*)TO->query_attackers() != ({ })) {
        return;
    }
	else 
        call_out("friend_or_foe", 1, TP);
        return;
    }
	
int friend_or_foe()
{
	int i;
	if(member_array("Enemy of the Legions of Serakii",TP->query_mini_quests())== 1 ){
        if(!random(6)){
			force_me("yell Enemies! Call reinforcements!");
		}	
	 force_me("kill " + TP->query_name() + "");

	 return 1;
	}
	else if(member_array("Serakii_Legions",TP->query_mini_quests())== 1 ){
             i = random(5);
        switch(i){
        case 0: force_me("say Welcome home.");
                break;
        case 1: force_me("nod " + TP->query_name() + "");
                break;
        case 2..4: break;
        }
	 return 1;
	}
   else{
  if(!random(10)) {force_me("say What do you want?"); }
    return 1; 
 }
}
