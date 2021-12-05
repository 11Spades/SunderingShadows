// Black Leather Whip


#include <std.h>
inherit "/d/common/obj/weapon/whip.c";

void create(){
        ::create();
        set_name("black leather whip");
        set_id(({"whip","black leather whip","leather whip"}));
        set_short("%^C241%^bla%^C244%^c%^C241%^k "+
		"l%^C095%^e%^C241%^ath%^C095%^e%^C241%^r "+
		"w%^C095%^h%^C245%^i%^C241%^p%^CRST%^");
        set_obvious_short("%^C241%^bla%^C244%^c%^C241%^k "+
		"l%^C095%^e%^C241%^ath%^C095%^e%^C241%^r "+
		"w%^C095%^h%^C245%^i%^C241%^p%^CRST%^");
        set_long("%^C245%^This eight foot %^C095%^leather "+
		"whip%^C245%^ has been %^C252%^braided %^C245%^together "+
		"from %^C241%^black leather cords%^C245%^ until it is "+
		"extremely strong. The handle is wrapped with a "+
		"more %^C095%^comfortable leather%^C245%^ for grip, "+
		"and the pommel has a small %^C241%^iron stud%^C245%^ "+
		"in it. At the end of the whip a small shard of %^C252%^"+
		"cold iron%^C245%^ to inflict an even more %^C124%^"+
		"wicked %^C245%^wound.\n%^CRST%^");
        set_value(10000);
        set_lore("%^C125%^The tool of slave masters and "+
		"overlords, thee whip can be a symbol of oppression "+
		"even coiled at the hip. The very sight of one can "+
		"send a person scurrying for safety.");

     set_property("enchantment",5);
         set_size(2);
     set_hit((:TO,"hit":));
}


int hit(object targ){
   if(!objectp(targ)) return 0;
   if(!random(5)){
      switch(random(4)){
         case 0..2:
            tell_room(environment(query_wielded()),"%^C245%^"+ETOQCN+"%^C245%^ "+
			"lashes "+targ->QCN+"%^C245%^ across the chest, the iron "+
			"shard ripping across them!%^CRST%^",({ETO,targ}));
            tell_object(ETO,"%^C245%^Your whip slashes "+
			"across "+targ->QCN+"%^C245%^'s chest and blood "+
			"splatters!%^CRST%^");
            tell_object(targ,"%^C245%^"+ETOQCN+"%^C245%^ cuts across "+
			"your chest with the barb on their whip!%^CRST%^");
			return roll_dice(3,4)+2;
         break;
         case 3:
            tell_room(environment(query_wielded()),"%^C095%^"+ETOQCN+"%^C095%^ "+
			"pulls "+ETO->QP+"%^C095%^ whip back and it flies towards "+targ->QCN+"%^C095%^'s "+
			"legs, tripping "+targ->QO+".%^CRST%^",({ETO,targ}));
            tell_object(ETO,"%^C095%^Flicking your wrist at "+targ->QCN+"%^C095%^, you "+
			"capture their legs and they start to fall.");
            tell_object(targ,"%^C095%^"+ETOQCN+"%^C095%^ pulls "+ETO->QP+"%^C095%^ whip "+
			"back and the coil tangles your legs, tripping you!%^CRST%^");
            if(!"/daemon/saving_throw_d.c"->reflex_save(targ,-25))
            targ->set_tripped(1,"You're trying to pick yourself up off the ground.");
            break;
         }
      return roll_dice(2,5)+3;
   }
   return 0;
}

