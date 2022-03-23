#include <std.h>
inherit ARMOUR;

#define COLORS ({"%^BOLD%^%^CYAN%^aquamarine%^RESET%^",\
"%^GREEN%^olive green",\
"%^BOLD%^%^CYAN%^azure",\
"%^BLUE%^indigo",\
"%^BOLD%^%^GREEN%^emerald green",\
"%^MAGENTA%^amethyst",\
"%^BOLD%^%^WHITE%^ivory",\
"%^BOLD%^%^BLUE%^ocean blue",\
"%^BOLD%^%^GREEN%^leaf green",\
"%^GREEN%^pine green",\
"%^BOLD%^%^BLUE%^cobalt blue",\
"%^BLUE%^navy blue",\
"%^GREEN%^forest green",\
"%^BOLD%^%^CYAN%^sky blue",\
"%^BOLD%^%^BLUE%^sapphire blue",\
"%^CYAN%^blue-green",\
"%^GREEN%^gray-green",\
"%^BOLD%^%^BLACK%^black",\
"%^ORANGE%^rich brown",\
"%^ORANGE%^dark brown",\
"%^ORANGE%^walnut brown",\
"%^RED%^brick red",\
"%^ORANGE%^peach",\
"%^BOLD%^%^GREEN%^lime green",\
"%^BOLD%^%^RED%^ruby red",\
"%^MAGENTA%^royal purple",\
"%^RED%^blood red",\
"%^MAGENTA%^violet",\
"%^ORANGE%^rusty orange",\
"%^BOLD%^%^RED%^rusty red",\
"%^BOLD%^%^RED%^reddish orange",\
"%^BOLD%^%^RED%^fiery red",\
"%^BOLD%^%^BLUE%^cornflower blue",\
"%^MAGENTA%^lavender",\
"%^BOLD%^%^MAGENTA%^carnation pink",\
"%^ORANGE%^light brown",\
"%^CYAN%^turquoise",\
"%^BOLD%^%^BLACK%^charcoal gray",\
"%^CYAN%^cyan blue",\
"%^BOLD%^%^WHITE%^rich cream",\
"%^BOLD%^%^WHITE%^cream",\
"%^BOLD%^%^WHITE%^white",\
"%^YELLOW%^saffron",\
"%^YELLOW%^lemon yellow",\
"%^ORANGE%^tangerine",\
"%^BOLD%^%^MAGENTA%^mauve",\
"%^RED%^crimson",\
"%^BOLD%^%^MAGENTA%^lilac",\
"%^YELLOW%^daffodil",\
"%^ORANGE%^beige",\
"%^ORANGE%^taupe",\
"%^BOLD%^%^BLACK%^sable",\
"%^ORANGE%^fawn",\
"%^BOLD%^%^BLACK%^pale gray",\
"%^BOLD%^%^BLACK%^stormy gray",\
"%^ORANGE%^dusty brown",\
"%^BOLD%^%^BLACK%^dark gray"\
})

int j, val;
string str, FABRIC, VAR, LENGTH;
void create_pants()
{
   j = random(sizeof(COLORS));
   str = COLORS[j];
   VAR = "a";
   if(str == "%^MAGENTA%^amethyst" || str == "%^BOLD%^%^GREEN%^emerald" || str == "%^BOLD%^%^CYAN%^aquamarine" || str == "%^BLUE%^indigo" || str == "%^GREEN%^olive green" || str == "%^BOLD%^%^WHITE%^ivory" || str == "%^BOLD%^%^CYAN%^azure" || str == "%^BOLD%^%^BLUE%^ocean blue") {
      VAR = "an";
   }
	switch(random(2)) {
      case 0:
         LENGTH = "shorts";
         break;
      case 1:
         LENGTH = "pants";
         break;
	}
   val = random(25);
   switch(val) {
      case 0..5:
         FABRIC = "burlap";
         set_long("This is a rather rough and uncomfortable pair "+
         "of "+LENGTH+" made of burlap that has been dyed "+VAR+" %^RESET%^"+
         ""+str+" %^RESET%^color. The best thing about these "+LENGTH+" is that "+
         "they will last for a long time.");
         break;
      case 6..10:
         FABRIC = "hemp";
         set_long("This pair of "+LENGTH+" is made out of sturdy"+
         " hemp that's been dyed "+VAR+" %^RESET%^"+str+" %^RESET%^color. It is slightly"+
         " itchy and rather uncomfortable to wear in the heat, but"+
         " appears very durable.");
         break;
      case 11..15:
         FABRIC = "cotton";
         set_long("This is a pair of "+LENGTH+" made of soft cotton"+
         " dyed "+VAR+" %^RESET%^"+str+" %^RESET%^shade. It is of a very good quality and"+
         " looks durable in addition to being comfortable. The front "+
         "buttons up, and there are loops for a belt.");
         break;
      case 16..20:
         FABRIC = "broadcloth";
         set_long("This is a pair of "+LENGTH+" made of broadcloth"+
         " dyed "+VAR+" %^RESET%^"+str+" %^RESET%^shade. The weave of the fabric creates "+
         "slight ridges, forming a pattern almost like boxes though all "+
         "in one shade.  The material is slightly more flexible than "+
         "cotton, but otherwise very similar.");
         break;
      case 21..24:
         FABRIC = "linen";
         set_long("This is a pair of "+LENGTH+" made of high quality"+
         " linen dyed "+VAR+" %^RESET%^"+str+" %^RESET%^shade. The material is thin but "+
         "stonger than cotton, creating a fabric that breathes easily, "+
         "but also wrinkles very easily.  Linen is often favored by "+
         "those in warmer climates.");
         break;
   }
   if(val < 5) {
      set_value(5);
   }
   else {
      set_value(val);
   }
   set_name("pants");
   set_type("clothing");
   set_limbs(({"right leg", "left leg"}));
   set_weight(3);
   set_short(capitalize(VAR)+" %^RESET%^"+str+" pair of "+FABRIC+" "+LENGTH+"%^RESET%^");
   set_id(({""+LENGTH+"","clothing",""+str+" "+LENGTH+"",""+FABRIC+" "+LENGTH+"",""+str+" "+FABRIC+" "+LENGTH+"","pair of "+LENGTH+""}));
}


void create()
{
   ::create();
   create_pants(); 
   set_size(random(3)+1);
   set_cointype("silver");
}