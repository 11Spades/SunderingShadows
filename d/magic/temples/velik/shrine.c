// Velik Shrine - By 'His Sojourner' - Implemented by Cher 

#include <std.h>
#include "velik.h"

inherit CROOM;

string seas,diety;
int FUNDS;


void create() {
    ::create();
    diety = "velik";
	set_terrain(RUINS);
    set_travel(RUTTED_TRACK);
    set_property("indoors",0);
    set_property("light",2);
    set_name("small shrine at the side of the road");
    set_short("%^C240%^small shrine%^C247%^ at the "+
	"side of the %^C058%^road%^CRST%^");

    seas = season(time());
	set_long("%^RESET%^blah%^RESET%^");
	switch(seas){

	case "summer": 
        set_long("%^RESET%^%^C101%^Set off to "+
		"the side of the %^RESET%^%^C059%^"+
		"road%^RESET%^%^C101%^, nestled against "+
		"the %^RESET%^%^C194%^mountains%^RESET%^%^C101%^"+
		", is a %^RESET%^%^C241%^small stone "+
		"shrine%^C101%^. The %^RESET%^%^C194%^"+
		"mountains %^RESET%^%^C101%^themselves tower "+
		"over you and protect the %^RESET%^%^C239%^"+
		"shrine %^RESET%^%^C101%^from most of "+
		"the %^RESET%^%^C074%^weather%^RESET%^%^C101%^ "+
		"and the %^RESET%^%^C088%^heat %^RESET%^%^C101%^of "+
		"the %^RESET%^%^C088%^summerstime season%^RESET%^%^C101%^"+
		". The %^RESET%^%^C058%^dust%^RESET%^%^C101%^ "+
		"from the %^RESET%^%^C060%^RESET%^%^trade "+
		"road %^RESET%^%^C101%^beside you drifts on the wind. "+
		"The %^RESET%^%^C239%^shrine %^RESET%^%^C101%^itself "+
		"is carved from a %^RESET%^%^C240%^solid chunk of "+
		"limestone%^C101%^ and on the front of it is "+
		"an %^RESET%^%^C238%^engraving%^RESET%^%^C101%^ "+
		"in %^RESET%^%^C238%^heavy text%^RESET%^%^C101%^. "+
		"Around the %^RESET%^%^C242%^shrine %^RESET%^%^C101%^"+
		"are %^RESET%^%^C184%^giant sunflowers%^C101%^ "+
		"and %^RESET%^%^C028%^thistles %^RESET%^%^C101%^that "+
		"add color to the area. Beside the %^RESET%^%^C241%^"+
		"shrine %^RESET%^%^C101%^is a giant pile "+
		"of %^RESET%^%^C238%^shackles %^RESET%^%^C101%^"+
		"and %^RESET%^%^C238%^chains %^RESET%^%^C101%^that have "+
		"been left as offerings. On the other side of "+
		"the %^RESET%^%^C241%^shrine %^RESET%^%^C101%^is a "+
		"large %^RESET%^%^C059%^secured donation "+
		"box%^RESET%^%^C101%^.\n%^CRST%^");

            set_listen("default","You hear the sounds "+
			"of %^C063%^birds %^CRST%^high in the %^C241%^rocks%^CRST%^.");
            set_smell("default","You smell %^C058%^rich "+
			"earth%^CRST%^ and %^C165%^flowers%^CRST%^.");

    break;


	case "spring": 
        set_long("%^RESET%^%^C101%^Set off to the side of "+
		"the %^RESET%^%^C060%^road%^RESET%^%^C101%^, nestled "+
		"against the %^RESET%^%^C194%^mountains%^RESET%^%^C101%^"+
		", is a %^RESET%^%^C241%^small stone shrine%^RESET%^%^C101%^. "+
		"The %^RESET%^%^C194%^mountains %^RESET%^%^C101%^themselves "+
		"tower over you and protect the shrine from most of "+
		"the %^RESET%^%^C069%^weather %^RESET%^%^C101%^and the "+
		"worst of the %^RESET%^%^C081%^springstime storms%^RESET%^%^C101%^"+
		". The road has been %^RESET%^%^C094%^churned up%^RESET%^%^C101%^ "+
		"and the sides are more %^RESET%^%^C094%^mud %^RESET%^%^C101%^than "+
		"anything else. The %^RESET%^%^C241%^shrine %^RESET%^%^C101%^itself "+
		"is carved from a %^RESET%^%^C241%^solid chunk of "+
		"limestone%^RESET%^%^C101%^ and on the front of it is "+
		"an %^RESET%^%^C238%^engraving %^RESET%^%^C101%^"+
		"in %^RESET%^%^C238%^heavy text%^RESET%^%^C101%^. %^RESET%^%^C190%^"+
		"Daffodils %^RESET%^%^C101%^poke through the %^RESET%^%^C094%^"+
		"soil %^RESET%^%^C101%^and you can see the start of %^RESET%^%^C028%^"+
		"other plants%^RESET%^%^C101%^ around the %^RESET%^%^C241%^"+
		"stone%^C101%^. Beside the %^RESET%^%^C241%^shrine %^RESET%^%^C101%^is "+
		"a giant pile of %^RESET%^%^C238%^shackles %^RESET%^%^C101%^"+
		"and %^C238%^chains %^RESET%^%^C101%^that have been left as "+
		"offerings. On the other side of the shrine is a %^RESET%^%^C060%^"+
		"large secured donation box%^RESET%^%^C101%^.\n%^CRST%^");

            set_listen("default","You hear the sounds "+
			"of %^C063%^birds %^CRST%^high in the %^C241%^rocks%^CRST%^.");
            set_smell("default","You smell %^C081%^fresh "+
			"rain%^CRST%^.");

    break;



    case "winter":
        set_long("%^C101%^Set off to the side of the %^RESET%^%^C060%^"+
		"road%^C101%^, nestled against the %^RESET%^%^C194%^mountains%^C101%^"+
		", is a %^RESET%^%^C242%^small stone shrine%^C101%^. "+
		"The %^RESET%^%^C194%^mountains %^RESET%^%^C101%^themselves tower "+
		"over you and protect the shrine from most of the %^RESET%^%^C195%^"+
		"weather %^RESET%^%^C101%^and creates a %^RESET%^%^C087%^"+
		"wind tunnel%^RESET%^%^C101%^. %^RESET%^%^C254%^Snow "+
		"drifts%^RESET%^%^C101%^ "+
		"up all around you and %^RESET%^%^C254%^piles %^RESET%^%^C101%^up "+
		"near the %^RESET%^%^C241%^shrine%^C101%^. The shrine itself is "+
		"carved from a %^RESET%^%^C241%^solid chunk of "+
		"limestone%^RESET%^%^C101%^ "+
		"and on the front of it is an %^RESET%^%^C238%^engraving %^RESET%^%^C101%^"+
		"in %^C238%^heavy text%^RESET%^%^C101%^. %^RESET%^%^C087%^Icicles %^C101%^"+
		"hang off the sides of the %^RESET%^%^C241%^altar %^RESET%^%^C101%^and "+
		"a %^RESET%^%^C059%^large secure donation box%^RESET%^%^C101%^. Beside "+
		"the shrine is a giant pile of %^RESET%^%^C238%^shackles %^RESET%^%^C101%^"+
		"and %^RESET%^%^C238%^chains %^RESET%^%^C101%^that have been left "+
		"as offerings.\n%^CRST%^");

            set_listen("default","You hear the %^C081%^wind %^C195%^"+
			"rip %^CRST%^through the %^C243%^pass%^CRST%^.");
            set_smell("default","You smell %^C242%^little "+
			"%^CRST%^in the %^C159%^cold%^CRST%^.");

    break;



    case "autumn":
        set_long("%^RESET%^%^C101%^Set off to the side of "+
		"the %^RESET%^%^C059%^road%^RESET%^%^C101%^, nestled against "+
		"the %^RESET%^%^C194%^mountains%^RESET%^%^C101%^, is "+
		"a %^RESET%^%^C241%^small stone shrine%^RESET%^%^C101%^. "+
		"The %^RESET%^%^C194%^mountains%^RESET%^%^C101%^ themselves "+
		"tower over you and protect the shrine from most of "+
		"the %^RESET%^%^C075%^weather%^RESET%^%^C101%^ and "+
		"the %^RESET%^%^C061%^storms %^RESET%^%^C101%^heralding "+
		"the coming %^RESET%^%^C074%^cold season%^C101%^. "+
		"%^RESET%^%^C124%^Thick piles of leaves%^RESET%^%^C101%^ "+
		"and %^RESET%^%^C095%^detritus %^RESET%^%^C101%^carried "+
		"here by the %^RESET%^%^C067%^storms %^RESET%^%^C101%^gathers "+
		"all around the %^RESET%^%^C241%^shrine %^RESET%^%^C101%^though "+
		"close to it has been cleaned so it is accessible. "+
		"The %^RESET%^%^C241%^shrine%^RESET%^%^C101%^ itself is "+
		"carved from a %^RESET%^%^C241%^solid chunk of limestone%^RESET%^%^C101%^ "+
		"and on the front of it is an %^RESET%^%^C238%^engraving "+
		"%^RESET%^%^C101%^in %^RESET%^%^C238%^heavy text%^RESET%^%^C101%^. "+
		"All around the %^RESET%^%^C241%^shrine %^RESET%^%^C101%^"+
		"are %^RESET%^%^C028%^giant thistles%^RESET%^%^C101%^ "+
		"with %^RESET%^%^C055%^bold purple flowers%^RESET%^%^C101%^ "+
		"and the %^RESET%^%^C059%^bent %^RESET%^%^C101%^and "+
		"broken %^RESET%^%^C059%^stalks%^RESET%^%^C101%^ "+
		"from %^RESET%^%^C190%^sunflowers%^RESET%^%^C101%^ "+
		"of season past. Beside the %^RESET%^%^C241%^shrine "+
		"%^RESET%^%^C101%^is a giant pile of %^RESET%^%^C238%^"+
		"shackles %^RESET%^%^C101%^and %^RESET%^%^C238%^chains "+
		"%^RESET%^%^C101%^that have been left as offerings. On "+
		"the other side of the shrine is a %^RESET%^%^C059%^large "+
		"secured donation box%^RESET%^%^C101%^.\n%^CRST%^");

            set_listen("default","You hear the sounds "+
			"of %^C063%^birds %^CRST%^high in the %^C241%^rocks%^CRST%^.");
            set_smell("default","You smell %^C081%^fresh "+
			"rain%^CRST%^.");

    break;



    }	

    set_items(([
        ({"mountains"}) : "The %^C059%^mountains %^CRST%^loom "+
		"over you on both sides",
        ({"shackles"}) : "%^C238%^shackles %^CRST%^lay in "+
		"piles near the %^C242%^altar%^CRST%^. Each have "+
		"been %^C060%^broken %^CRST%^and on the %^C238%^cuffs %^CRST%^the name of the freed slave has been scrawled, even if it "+
		"is just a small %^C242%^symbol%^CRST%^.",
        ({"chains"}) : "The %^C238%^chains %^CRST%^that "+
		"lay here have been %^C243%^destroyed%^CRST%^. Each link has been cut meticulously.",
		({"road"}) : "You can see the %^C060%^road %^CRST%^from "+
		"here heading north and south. It is a busy %^C058%^trade road%^CRST%^ and %^C172%^caravans %^CRST%^and "+
		"%^C241%^soldiers %^CRST%^move along it "+
		"constantly.",
        ({"box","donation box"}) : "A %^C060%^sturdy "+
		"box%^CRST%^ is here for donations in %^C184%^gold%^CRST%^. You realize "+
		"how the box is made that you can %^C080%^>donate<%^CRST%^ gold "+
		"but you could never take from it.",
        ({"altar","shrine"}) : "The %^C241%^shrine %^CRST%^is simple, "+
		"a %^C242%^block of stone%^CRST%^ without much ornamentation "+
		"except a %^C238%^heavy text engraving%^CRST%^ you "+
		"could %^C194%^>read<%^CRST%^. On the top of the altar "+
		"is a simple mat.",
        ({"heavy text","engraving"}) : "This %^C242%^text %^CRST%^has "+
		"been etched with a %^C241%^heavy chisel%^CRST%^ and "+
		"you could %^C194%^>read<%^CRST%^ if it "+
		"you wanted.\n",
    ]));

	set_exits(([
		"east": "/d/shadow/room/pass/passn1",
	]));

}

void reset(){
   ::reset();
   if(!present("spirit_of_the_shrine")){
      new(MOBS"shrine_spirit.c")->move(TO);
   }
}

void init() {
    ::init();
    add_action("read_fun", "read");
    add_action("donate_fun","donate");
}

int read_fun(string str,object who){

    if(!str) {
       tell_object(TP,"%^BLACK%^%^BOLD%^Read what?\n%^RESET%^");
       return 1;
    }

    if((str == "heavy text") || (str == "engraving")){
        tell_object(TP,"%^C187%^you read the text around the stone "+
        "slab..\n%^CRST%^\n %^C148%^Every freed soul who walks this road bears the name Velik on their lips, the freedom of Velik as their wings, and the strength of Velik in their heart. We will continue to free the slaves, topple the machines of slavery, and end the tryrany of corrupt governments. Stay awhile and shed your chains brother and sister, for tomorrow we fight.%^CRST%^\n");
        tell_room(ETP,"%^C187%^"+TPQCN+" %^C187%^reads the writing.%^RESET%^",TP);

       return 1;
    }
    return 0;
}

int donate_fun(string str) {
   string type;
   int x, amount, amt2;
   object what;
   if(TP->query_bound() || TP->query_unconscious()){
      TP->send_paralyzed_message("info",TP);
      return 1;
   }
   if(!str) {
      notify_fail("Correct syntax: <donate [amount] [type]\n");
      return 0;
   }
    if(TP->query_property("dominated"))
        return notify_fail("The god senses your true feelings and does not
accept your donation.\n");

   if(sscanf(str, "%d %s", amount, type) != 2) {
      notify_fail("Please try either <donate [amount] [type]>\n");
      return 0;
   }
   if((int)TP->query_money(type) < amount) {
      notify_fail("You check your pockets and realize you do not have that "
        "many "+type+"!\n");
      return 0;
   }
   if(amount < 0) {
      notify_fail("No, you can't do that and yes, we're watching!\n");
      return 0;
   }
    TP->use_funds(type,amount);
    write_file("/realms/loki/velik/donation.log",TP->query_name() +
        " donated "+ amount +" " +type+ " on "+ctime(time())+"\n");
    
	tell_object(TP,"You slip the "+amount+" "+type+" coins into the donation box.");
   switch(amount + random(50)) {
      case 0..30 :   tell_room(ETP,TPQCN+" drops a few "+type+" coins into "
                       "the donation box.",TP);
                     break;
      case 31..100 : tell_room(ETP,TPQCN+" donates a handful of "+type+" coins "
                        "to the donation box.",TP);
                     break;
      case 101..475: tell_room(ETP,TPQCN+" slips a few handfuls of "+type+
                       " coins into the donation box.",TP);
                     break;
      case 476..1475: tell_room(ETP,TPQCN+" donates several handfuls of "+type+
                       " coins to the donation box.",TP);
                     break;
      case 1476..4975 : tell_room(ETP,TPQCN+" empties a pouch of "+type+
                       " coins into the donation box.",TP);
                      break;
      case 4976..14050 : tell_room(ETP,TPQCN+" empties a small sackful"
                       " of "+type+" coins into the donation box.",TP);
                      break;
      case 14051..50000 : tell_room(ETP,TPQCN+" empties a large sack"
                       " of "+type+" coins into the donation box.",TP);
                      break;
      default : tell_room(ETP,TPQCN+" donates some "+type+
                       " coins to the temple's donation box.",TP);
                      break;
   }
   return 1;
}
