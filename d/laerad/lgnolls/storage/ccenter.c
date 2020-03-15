//ccenter Template  - Essyllis - May - 2014


#include <std.h>
#include "../lgnoll.h"
#define RANDSTUFF "/d/common/daemon/randstuff_d"

inherit CROOM;

object ob;
void pick_critters();
int searched;


void create() {
	searched=0;
    pick_critters();
    set_repop(45);
    ::create();
    set_terrain(STONE_BUILDING);
    set_travel(PAVED_ROAD);
    set_property("indoors",0);
    set_property("light",2);
    set_property("no teleport",0);
    set_name("Gnoll main camp");
    set_short("%^ORANGE%^gnoll main camp%^RESET%^");
    set_long("%^GREEN%^You are standing in what must be the %^ORANGE%^gn%^BOLD%^%^BLACK%^o%^RESET%^%^ORANGE%^lls' "+
	"%^GREEN%^main-camp%^YELLOW%^. %^RESET%^%^GREEN%^A multitude of huts and crude leather tents litter the whole "+
	"area. The smell and sounds of %^ORANGE%^gn%^BOLD%^%^BLACK%^o%^RESET%^%^ORANGE%^lls "+
	"%^BOLD%^%^BLACK%^'%^RESET%^%^ORANGE%^communicating%^BOLD%^%^BLACK%^' %^RESET%^%^GREEN%^can be heard from "+
	"other places in the camp. Luckily the %^BOLD%^%^BLACK%^h%^RESET%^u%^BOLD%^%^BLACK%^ts %^RESET%^%^GREEN%^and "+
	"%^BOLD%^%^BLACK%^t%^RESET%^e%^BOLD%^%^BLACK%^nts %^RESET%^%^GREEN%^provide ample cover to move around unnoticed. "+
	"Often a %^BOLD%^%^BLACK%^fight %^RESET%^%^GREEN%^between two %^ORANGE%^gn%^BOLD%^%^BLACK%^o%^RESET%^%^ORANGE%^lls "+
	"%^GREEN%^or some %^CYAN%^poor victim %^GREEN%^of their appetite can be heard%^ORANGE%^, %^GREEN%^muffling out the "+
	"sound yo%^RED%^u %^GREEN%^might make%^YELLOW%^. %^RESET%^%^GREEN%^Walking around the camp one will have to watch "+
	"their steps%^YELLOW%^. %^RESET%^%^MAGENTA%^H%^RED%^a%^MAGENTA%^lf-e%^RED%^a%^MAGENTA%^ten %^CYAN%^victims %^GREEN%^of "+
	"various races lay spread all over the ground in various degrees of %^MAGENTA%^decomposition%^YELLOW%^.%^RESET%^\n");
	
    set_smell("default","%^ORANGE%^It smells badly of %^RED%^r%^MAGENTA%^o%^RED%^tt%^MAGENTA%^e%^RED%^n fl%^MAGENTA%^e%^RED%^sh %^ORANGE%^and %^BOLD%^%^BLACK%^o%^RESET%^%^GREEN%^i%^BOLD%^%^BLACK%^ly m%^RESET%^%^GREEN%^u%^BOLD%^%^BLACK%^sk%^RESET%^");
    set_listen("default","%^ORANGE%^You hear %^BOLD%^%^BLACK%^gnolls f%^RESET%^%^RED%^i%^BOLD%^%^BLACK%^ght%^RESET%^%^RED%^i%^BOLD%^%^BLACK%^ng %^RESET%^%^ORANGE%^and %^BOLD%^%^BLACK%^communicating %^RESET%^%^ORANGE%^all around you%^BOLD%^%^BLACK%^.%^RESET%^");

    set_items
    (([	
        ({"floor", "ground", "outcroppings"}) : "%^ORANGE%^The ground is littered with %^WHITE%^b%^BOLD%^o%^RESET%^nes %^ORANGE%^and %^MAGENTA%^rubbish %^ORANGE%^thrown from the huts. Tread carefully!%^RESET%^",
        ({"hut", "huts", "tent", "tent"}) : "%^ORANGE%^These living quarters of the gnolls offer little protection from the %^BOLD%^elements%^RESET%^%^ORANGE%^. But it is still roof over the head. Most of the huts don't even have doors.%^RESET%^ ",
        ({"dog", "dogs", "dog houses", "dog house"}) : "%^ORANGE%^These huts or houses are just as crude and primitive as the rest but they are still different. They are empty except for rotten meat in some of them.%^RESET%^",
		({"victim","victims","corpse","corpses"}):"%^ORANGE%^The half eaten victims seem to be of almost any race the gnolls have been able to catch. The majority consist of %^BOLD%^Thri-kreen %^RESET%^%^ORANGE%^and %^BOLD%^%^BLACK%^humans.%^RESET%^",
	]));
set_search("hut",(:TO,"searching":));
set_search("huts",(:TO,"searching":));
set_search("tent",(:TO,"searching":));
set_search("tents",(:TO,"searching":));
	}

void searching(){
	if(searched){notify_fail("Everything is turned over, someone has already been here."); return 0;}
	searched=1;
	switch(random(50)){
	
	case 0:
	tell_object(TP,"%^BOLD%^%^BLACK%^Black eyes %^RED%^glare at you from within one of the huts ... You have disturbed something dangerous!");
	tell_room(ETP,""+TP->QCN+" %^BOLD%^%^BLACK%^takes a step back from one of the huts, just as you hear a %^RED%^low growling!",TP);
	new(MOBS"gnollhunter")->move(TO);
	break;
	
	case 1..10:
	tell_room(ETP,"As "+TP->QCN+" tries to search a hut, a gnoll rushes out and attacks!",TP);
	tell_object(TP,"As you try to search the hut, a gnolls rushes out and attacks!");
	new(MOBS"gnollwarrior")->move(TO);
	break;
	
	case 11..20:
	tell_room(ETP,"As "+TP->QCN+" tries to search a hut, gnolls rush out and attack!",TP);
	tell_object(TP,"As you try to search the hut, gnolls rush out and attack!");
	new(MOBS"gnollpriest")->move(TO);
	new(MOBS"gnollbarb")->move(TO);
	break;
	
	case 21..30:
	tell_room(ETP,""+TP->QCN+" finds something as "+TP->QS+" searches the hut.",TP);
	tell_object(TP,"You find something as you search the hut.");
	RANDSTUFF->find_stuff(TO,"midscroll");
	RANDSTUFF->find_stuff(TO,"stuff");
	break;
	
	case 31..35:
	tell_room(ETP,""+TP->QCN+" finds something as "+TP->QS+" searches the hut.",TP);
	tell_object(TP,"You find something as you search the hut.");
	RANDSTUFF->find_stuff(TO,"potion");
	RANDSTUFF->find_stuff(TO,"coins");
	break;
	
	case 36..49:
	  ob = new("/d/common/obj/potion/extra_heal");
      ob->set_uses(random(10)+5);
      ob->move(ETP);
      tell_object(TP,"You find some healing vials");
      tell_room(ETP,""+TP->QCN+" finds some healing vials",TP);
	break;
	}
	return;
}
	
void reset(){
   ::reset();
   searched=0;
   switch(random(6)){
      case 0..2:  tell_room(TO,"%^BOLD%^%^BLACK%^You hear a %^ORANGE%^li%^RED%^o%^ORANGE%^n's "+
	  "%^RED%^roar %^BLACK%^followed by the death-cry of a %^RESET%^%^ORANGE%^gnoll.");
               break;
      case 3..4:  tell_room(TO,"%^ORANGE%^A %^CYAN%^gust of wind blows %^ORANGE%^through the "+
	  "camp, lifting the %^BOLD%^%^BLACK%^stink %^RESET%^%^ORANGE%^of %^MAGENTA%^death %^ORANGE%^and "+
	  "%^MAGENTA%^decay %^ORANGE%^for a precious few seconds.");
               break;
      case 5:  tell_room(TO,"%^BOLD%^%^BLACK%^A %^RED%^horrible death cry %^BLACK%^of another of the "+
	  "gnolls' victims can he hear from somewhere in the camp.");
               break;
         }
}


void pick_critters(){
   switch(random(5)){
        case 0:   set_monsters(
({MOBS"gnollwarrior",MOBS"gnollpriest"}),({random(2),1}) );
                   break;
         case 1:   set_monsters(
({MOBS"gnollwarrior",MOBS"gnollbarb"}),({random(2),1}) );
                   break;
         case 2:   set_monsters(
({MOBS"gnollpriest",MOBS"gnollbarb"}),({random(2)+1,random(2)}) );
                   break;
         case 3..4: break;
   }
}

