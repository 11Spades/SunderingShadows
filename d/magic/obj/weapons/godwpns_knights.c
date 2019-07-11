// magic sword inherit for spells

#include <std.h>
inherit WEAPON;
string owner;

void create(){
    ::create();
        set_name("godweapon");
        set_short("a shiney godly weapon");
        set_long("This is a magical weapon that you can't quite"+
                " discern its purpose.  If you can see this weapon,"+
                " something is broken, contact a wiz!");
        set_id(({"godweapon"}));
        set_type("magicslashing");
        set_weight(0);
        set_value(0);
        set("no curse",1);
        set_prof_type("medium blades");
        set_weapon_prof("simple");
        set_wc(1,8);
        set_large_wc(1,10);
        set_size(2);
        set_wield((:TO, "extra_wield":));
        set_unwield((:TO,"extra_unwield":));
        set_property("able to cast",1);

}

void init(){
    int clevel,ench;

   ::init();
   if(stringp(owner)) return;
   if(interactive(TP) && TP == ETO){
       owner = TPQN;
   }
/*
Moved this to the spell because it was not providing the proper enchantment
~Circe~ 8/17/15

   clevel = TP->query_guild_level("cleric");
   ench = ((int)TP->query_guild_level("cleric"))/7; 
   if(ench < 1) ench = 1;
   if(ench > 5) ench = 5;
   set_property("enchantment",clevel/7);
   while((int)(query_property("enchantment")) < 0){
      remove_property("enchantment");
      set_property("enchantment",clevel/7);
   }
*/
}

int extra_wield(){
    if(interactive(TP) && owner != (string)TPQN){ 
        tell_object(TP,"You are not allowed to wield this weapon.");
        return 0;
    }
    if(objectp(ETO)) ETO->add_attack_bonus(2);
    return 1;
}

int extra_unwield(){
    if(objectp(ETO)) ETO->add_attack_bonus(-2);
    return 1;
}

int drop(){
    tell_object(TP,"Your hand will not release the divine weapon!");
    return 1;
}

int save_me(string file){ return 1;}
int is_ok_wield() { return 1; }
