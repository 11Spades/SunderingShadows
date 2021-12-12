// Hands of Equis - LoKi


#include <std.h>
inherit "/d/common/obj/weapon/claw.c";


void create() {
    ::create();
   set_id(({"knuckles","hand of the equis","iron knuckles"}));
   set_name("Hand of the Equis");
   set_short("%^RESET%^%^BOLD%^%^BLACK%^Ha%^RESET%^%^WHITE%^n%^RESET%^%^BOLD%^"+
"%^BLACK%^d of %^RESET%^%^ORANGE%^t%^RESET%^%^BOLD%^%^BLACK%^he E%^RESET%^"+
"%^ORANGE%^q%^RESET%^%^BOLD%^%^BLACK%^uis%^RESET%^");
   set_obvious_short("%^RESET%^%^BOLD%^%^BLACK%^Ir%^RESET%^%^WHITE%^o%^RESET%^"+
"%^BOLD%^%^BLACK%^n knuckl%^RESET%^%^WHITE%^e%^RESET%^%^BOLD%^%^BLACK%^s%^RESET%^");
   set_long("%^RESET%^%^BOLD%^%^BLACK%^These knuckles have been made from what "+
"looks like the reclaimed %^RESET%^%^ORANGE%^leath%^RESET%^%^WHITE%^e%^RESET%^"+
"%^ORANGE%^r %^RESET%^%^BOLD%^%^BLACK%^from a horse's bridle. It wraps around "+
"the wielder's hand and covers the knuckles with a %^RESET%^%^ORANGE%^thi%^RESET%^"+
"%^WHITE%^c%^RESET%^%^ORANGE%^k band of le%^RESET%^%^WHITE%^a%^RESET%^%^ORANGE%^ther"+
" %^RESET%^%^BOLD%^%^BLACK%^studded with small ir%^RESET%^%^WHITE%^o%^RESET%^%^BOLD%^"+
"%^BLACK%^n bo%^RESET%^%^WHITE%^l%^RESET%^%^BOLD%^%^BLACK%^ts. Even the original "+
"%^RESET%^%^YELLOW%^cl%^RESET%^%^ORANGE%^a%^RESET%^%^YELLOW%^sps %^RESET%^%^BOLD%^"+
"%^BLACK%^still hold the weapon together. The %^RESET%^%^ORANGE%^leath%^RESET%^"+
"%^WHITE%^e%^RESET%^%^ORANGE%^r %^RESET%^%^BOLD%^%^BLACK%^itself is fine and oiled"+
", the ir%^RESET%^%^WHITE%^o%^RESET%^%^BOLD%^%^BLACK%^n polished and clean. %^RESET%^");
   set_item_bonus("damage bonus",4);
   set_property("enchantment",6);
   set_hit((:TO,"hit_func":));
   set_wield((:TO,"wield_func":));
   set_unwield((:TO,"unwield_func":));
   set_property("lore difficulty",15);
   set_lore("%^RESET%^%^BOLD%^%^BLACK%^The hand of Equis bears its history from the "+
"horse of the same name. A massive warhorse of legendary strength and loyalty, Equis "+
"was matchless. At the fall of Karon'dale to Ogre-Magi forces, Equis stood over her "+
"fallen rider for a day and a night, felling opponents as readily as any warrior. "+
"When she finally fell, reinforcements from the Black Fortress claimed her saddle "+
"and created this weapon, so that her legend could live on.\n"+
"  %^WHITE%^%^BOLD%^- From the history of Karon'dale, Our Shared Shame%^RESET%^");
 
}

int wield_func(object targ){
        tell_room(EETO,"%^RESET%^%^ORANGE%^As "+ETOQCN+" %^RESET%^%^ORANGE%^wraps the leather of "+
"the "+query_short()+", %^RESET%^%^ORANGE%^knuckles around their hand they nod.%^RESET%^",({ETO,targ}));
        tell_object(ETO,"%^RESET%^%^ORANGE%^You wrap the "+query_short()+"%^RESET%^"+
"%^BOLD%^ leather around your hand. In your head you hear the desperate call of a horse, and "+
"you feel her sacrifice.%^RESET%^");
        return 1;
}   

int unwield_func(object targ) { 
        tell_room(EETO,"%^RESET%^%^RED%^"+ETOQCN+"%^RESET%^%^RED%^ slowly unwraps the leather "+
"and sets the knuckles aside.%^RESET%^",({ETO,targ}));
        tell_object(ETO,"%^RESET%^%^RED%^As you unwrap the "+query_short()+" %^RESET%^"+
"%^RED%^you feel the tide of battle failing...%^RESET%^");
        return 1;
}

int hit_func(object targ){
        if(!objectp(targ)) return 0;
        if(!objectp(ETO)) return 0;
            if(random(1000) < 50){
                tell_room(EETO,"%^BOLD%^%^RED%^"+ETOQCN+"%^BOLD%^%^RED%^ growls and releases a "+
"flurry of blows against "+targ->QCN+"%^BOLD%^%^RED%^.%^RESET%^",({ETO,targ}));
                tell_object(ETO,"%^BOLD%^%^RED%^You hear the desperate cry of a horse and leap "+
"forward, bashing against %^BOLD%^%^RED%^"+targ->QCN+"%^BOLD%^%^RED%^ repeatedly.%^RESET%^"); 
                tell_object(targ,"%^BOLD%^%^RED%^You are forced back as "+ETOQCN+"%^BOLD%^%^RED%^ "+
"launches at you!%^RESET%^");
                ETO->execute_attack();
                ETO->execute_attack();
               return 1;       
            }
}

