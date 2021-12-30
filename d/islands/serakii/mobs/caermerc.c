//random merc - LoKi

#include <std.h>
#include "../serakii.h"

inherit MONSTER;

void make_me();

        string theclass,race;

void create(){
   ::create();
   set_name("mercenary");
   set_id(({"mercenary"}));
   set_short("mercenary");
   set_hd(25,12);

   set_stats("strength",18);
   set_stats("dexterity",18);
   set_stats("wisdom",18);
   set_stats("intelligence",18);
  set_alignment(5);
   set_size(2);
   set_body_type("human");
   set_wielding_limbs(({"right hand","left hand"}));
   set("aggressive",1);
 
  set_class("fighter");
   set_guild_level("fighter",30);
  set_mlevel("fighter",30);


   make_me();
   set_property("no random treasure", 1);
   set_property("not random monster", 1);
   set_new_exp(35, "low");
// set_speed(20);
                set_nogo(({ "/d/islands/serakii/ruins/1" }));
}

void make_me(){
        object ob;
        int i,j,k;
        string theclass,race;
        i = random(5);
        switch(i){
        case 0: race = "human";
                break;
        case 1: race = "dwarf";
                break;
       case 2: race = "half-elf";
                break;
        case 3: race = "elf";
                break;
        case 4: race = "human";
                break;
        }

        set_race(race);


       i = random(3);

        switch(i){
       case 0: theclass = "swords";
                break;
        case 2: theclass = "dusk";
                break;
       case 1: theclass = "dragoon";
        }


        switch(theclass){
        case "swords":
            set_long("This soldier wears little heavy armor, just a %^C248%^breastplate%^CRST%^, and instead favors %^C075%^light clothing%^CRST%^. They wear a %^C094%^large hat %^CRST%^with a %^C045%^giant feather%^CRST%^ extending from it. %^C040%^Brightly colored pantaloons%^CRST%^ have been slashed to reveal contrasting %^C063%^colored fabric%^CRST%^ below, and flare out before ending in %^C094%^high leather boots%^CRST%^. At their side is a %^C245%^single sword%^CRST%^ and on their other arm they wear a %^C248%^buckler%^CRST%^. A %^C124%^crimson sash%^CRST%^ over their shoulder is tied with a pin in the shape of a %^C243%^broken sword%^CRST%^, denoting this as a member of the mercenary company Chapter of Swords.\n");
            set_short("%^C111%^A %^CRST%^" +query_race()+ "%^C111%^ sw%^C040%^a%^C045%^s%^C111%^hb%^C046%^u%^C111%^ckl%^C078%^e%^C111%^r%^CRST%^");
                add_id(({"swashbuckler","swords","chapter of swords"}));
               break;
        case "dusk":
                        set_long("A monk dressed in a %^C061%^robe%^CRST%^, this young woman walks with utmost %^C111%^silence%^CRST%^ and %^C175%^grace%^CRST%^. Her head has been %^C175%^shaved%^CRST%^ and beyond a simple %^C244%^iron collar%^CRST%^ finished with an %^C124%^uncut ruby%^CRST%^ she does not wear any other jewellry. In her hands she casually holds %^C246%^metal fans%^CRST%^ and on her feet are simple %^C094%^leather sandals%^CRST%^. On the back of her robe is the symbol of a %^C057%^single open eye%^CRST%^, showing this monk as a member of the Sisters of Dusk.\n");
            set_short("%^C055%^A s%^C057%^i%^C055%^le%^C057%^n%^C055%^t %^CRST%^" +query_race()+ "%^C054%^ mo%^C056%^n%^C054%^k%^CRST%^"); 
                add_id(({"monk","silent monk","sister of dusk"}));
            break;
        case "dragoon":
            set_long("Dressed in %^C251%^silver chainmail%^CRST%^ covered by a %^C231%^white satin tabard%^CRST%^, this soldier hefts a %^C248%^heavy kite shield%^CRST%^ and at their side hangs a heavy %^C246%^morningstar%^CRST%^. Heavy %^C248%^plate greaves%^CRST%^ and %^C095%^boots%^CRST%^ complete their gear. It is obvious from looking at them and the gear that this is no parade soldier but a veteran who has seen %^C088%^combat%^CRST%^ several times. Across the shield and tabard is the symbol of a %^C243%^dragon's head%^CRST%^ in profile, showing this soldier as a member of the Dragoon Irregulars.\n");
            set_short("%^C246%^A h%^C250%^e%^C246%^avily a%^C250%^r%^C246%^mor%^C249%^e%^C246%^d %^CRST%^" +query_race()+ "%^C246%^ s%^C250%^o%^C246%^ldi%^C250%^e%^C246%^r%^CRST%^");  
                add_id(({"soldier","armored soldier","dragoon"}));
            break;
        }
}
