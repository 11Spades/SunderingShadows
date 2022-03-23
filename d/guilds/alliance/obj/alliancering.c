//Updated with color and lore, last change 4/24/01 - Octothorpe 1/2/10

#include <std.h>

inherit "/std/guild.c";

void create(){
   ::create();
   set_name("Signet Ring");
   set_id(({"alliance ring","ring","signet ring"}));
   set_obvious_short("%^RESET%^%^BOLD%^platinum %^ORANGE%^signet %^WHITE%^ring%^RESET%^");
   set_short("%^RESET%^%^BOLD%^%^RED%^A%^ORANGE%^l%^RED%^l%^RESET%^%^RED%^i%^BOLD%^an%^ORANGE%^c%^RED%^e %^WHITE%^R%^ORANGE%^eb%^RED%^o%^ORANGE%^rn Signet %^WHITE%^Ring%^RESET%^");
   set_long("%^RESET%^%^BOLD%^%^BLACK%^A %^WHITE%^gleam %^BLACK%^catches the eye from this %^RESET%^finely wrought %^BOLD%^platinum %^RESET%^signet ring%^BOLD%^%^BLACK%^. Set in its center is an %^RESET%^onyx disc %^BOLD%^%^BLACK%^with a %^ORANGE%^f%^RED%^l%^RESET%^%^ORANGE%^a%^RED%^m%^YELLOW%^i%^RED%^n%^ORANGE%^g longsword %^RESET%^e%^BOLD%^%^BLACK%^t%^RESET%^ch%^BOLD%^%^BLACK%^ed into it. The %^WHITE%^mithril blade %^BLACK%^s%^WHITE%^hine%^BLACK%^s %^ORANGE%^bright %^BLACK%^against the %^RESET%^black backdrop%^BOLD%^%^BLACK%^. Made from %^RESET%^%^RED%^ru%^BOLD%^b%^RESET%^%^RED%^y dust%^BOLD%^%^BLACK%^, the %^ORANGE%^f%^RED%^l%^RESET%^%^ORANGE%^a%^BOLD%^m%^RED%^e%^ORANGE%^s %^BLACK%^that %^RED%^lick %^BLACK%^the %^WHITE%^sword %^RESET%^f%^YELLOW%^l%^RESET%^i%^YELLOW%^c%^RESET%^k%^YELLOW%^e%^RESET%^r %^BOLD%^%^BLACK%^and %^ORANGE%^dance %^BLACK%^like %^RED%^live t%^RESET%^%^ORANGE%^e%^BOLD%^n%^RESET%^%^RED%^d%^YELLOW%^ri%^RED%^l%^RESET%^%^RED%^s%^WHITE%^. %^BOLD%^%^BLACK%^At a certain angle, the %^ORANGE%^f%^RED%^l%^RESET%^%^ORANGE%^a%^BOLD%^m%^RED%^e%^ORANGE%^s %^BLACK%^resemble a %^WHITE%^ph%^ORANGE%^oen%^WHITE%^ix%^BLACK%^, encircling the sword. Along the body of the ring are faint traces of %^WHITE%^feathers%^BLACK%^, as though the %^ORANGE%^wings %^BLACK%^of the %^WHITE%^p%^ORANGE%^hoen%^WHITE%^ix spread %^BLACK%^out to %^ORANGE%^hug %^BLACK%^the wearer's finger. There is something %^RESET%^written %^BOLD%^%^BLACK%^on the inside of the band.%^RESET%^");
   set_lore("Rings of this design were once used as symbols of "+
      "membership in the Alliance of Light.  The Alliance was founded "+
	  "during the early part of the 640s SG out of the remnants of the "+
	  "Order of Metallic Dragons in order to combat the forces of evil "+
	  "in the region.  The Alliance is perhaps best known for its "+
	  "prolonged hostilities with the Raiders in Night's Cloak/Tempered "+
	  "Blades, which lasted through much of the '40s.  Many famous "+
	  "adventurers were members of the Alliance, such as Tanis, Korath, "+
	  "Ungrim, Zeal, Tanamen, Xodor, Vrax, and Brenamen.  Due to "+
	  "internal disagreements on the organization's direction, and "+
	  "renewed pressure from the Tempered Blades, the Alliance suddenly "+
	  "disbanded in 650 SG. In 750 SG, in the face of unspeakable darkness " + 
      "and the rising of Ashra, the Alliance Reborn was formed, founded on " +
      "the values of those days gone by. Through determination and grit, the " +
      "Alliance Reborn was able to awaken Edea to face Ashra and restore the balance.");
   set_type("ring");
   set_limbs(({"right hand"}));
   set_weight(1);
    set_guild_name("Alliance Reborn");
   set_guild_object("/d/guilds/alliance/obj/alliancering.c");
   set_property("lore difficulty",17);
   set_wear((:TO,"wear_fun":));
   set_remove((:TO,"remove_fun":));
}

/*void init(){
   ::init();
   if(!objectp(TO)) {
      message("info","The ring rejects you.",TP);
      return;
   }
   ETO->force_me("wear alliance ring");
}*/

int wear_fun(){
   string mname = ETO->query_name();
   if(mname == "zeal" || mname == "ungrim" || mname == "vrax" || mname == "brenamen" || mname == "korath"){
      tell_object(ETO,"%^BOLD%^As you wear the signet ring, you are "+
	     "reminded of your friends that are long gone, and the triumphs "+
		 "of the %^YELLOW%^Alliance Reborn %^WHITE%^that have faded "+
		 "from history.%^RESET%^");
	  tell_room(EETO,"%^BOLD%^"+ETOQCN+" appears to be fortified with "+
	     "renewed purpose as he wears the signet ring.%^RESET%^",ETO);	 
	  return 1;
   }
   ETO->set_property("good item",1);
   return 1;
}

int remove_fun(){
   ETO->set_property("good item",-1);
   return 1;
}
