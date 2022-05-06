// Oak and Iron Bardiche Flying Wind - LoKi 2021


#include <std.h>
inherit "/d/common/obj/weapon/bardiche.c";

void create(){
        ::create();
        set_name("Flying Wind");
        set_id(({"bardiche","oak and iron bardiche","flying wind"}));
        set_short("%^C078%^Fly%^C110%^i%^C078%^ng Wi%^C110%^n%^C078%^d%^CRST%^");
        set_obvious_short("%^C094%^oak%^C246%^ and %^C243%^iron%^C246%^ bardiche%^CRST%^");
        set_long("%^C248%^This %^C253%^pole arm%^C248%^ is dominated by a %^C244%^massive curved blade%^C248%^ that in itself is as long as most common blades. The %^C094%^arm%^C248%^ of the weapon is made from %^C095%^oak%^C248%^ and has been %^C100%^treated%^C248%^ and %^C138%^varnished%^C248%^ till it can withstand any %^C252%^force%^C248%^. The %^C242%^curved blade%^C248%^ is %^C243%^iron%^C248%^. At the top of the pole and behind the %^C242%^blade%^C248%^ are two small streamers, one %^C111%^blue%^C248%^ and the other %^C077%^green%^C248%^.\n%^CRST%^\n");
        set_value(10000);
        set_lore("%^C042%^It is said that the Flying Wind was a gift from a high ranking Priestess of Seija when the First Corp, Arnuf Brock's original company, saved the priestess from pirates off the coast of Serakii.%^CRST%^\n");

     set_property("enchantment",5);
     set_hit((:TO,"hit":));
}


int hit(object targ){
   if(!objectp(targ)) return 0;
   if(!random(5)){
      switch(random(4)){
         case 0..2:
            tell_room(environment(query_wielded()),"%^C046%^"+ETOQCN+"%^C046%^ "+
                        "slashes "+targ->QCN+"%^C046%^ wickedly with the blade of the bardiche!%^CRST%^",({ETO,targ}));
            tell_object(ETO,"%^C046%^You step back and slash "+targ->QCN+"%^C046%^ with the blade of your bardiche!%^CRST%^");
            tell_object(targ,"%^C046%^"+ETOQCN+"%^C046%^ slashes you wickedly with the blade of their bardiche!%^CRST%^");
                        return roll_dice(3,4)+2;
         break;
         case 3:
            tell_room(environment(query_wielded()),"%^C138%^"+ETOQCN+"%^C138%^ "+
                        "turns and slams the wooden shaft against "+targ->QCN+"%^C138%^'s "+
                        "legs, knocking "+targ->QO+"%^C138%^ over!%^CRST%^",({ETO,targ}));
            tell_object(ETO,"%^C138%^With a grin you slam the shaft of your bardiche against "+targ->QCN+"%^C138%^'s legs.%^CRST%^");
            tell_object(targ,"%^C138%^"+ETOQCN+" slams "+ETO->QP+"%^C138%^ bardiche and bashes your legs, knocking you over!%^CRST%^");
            if(!"/daemon/saving_throw_d.c"->reflex_save(targ,-25))
            targ->set_tripped(1,"You're trying to pick yourself up off the
ground.");
            break;
         }
      return roll_dice(2,5)+3;
   }
   return 0;
}
