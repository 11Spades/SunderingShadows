// Nilith's Bagman - Serakii - LoKi 2022	

#include <std.h>
#include <daemons.h>
#include "../serakii.h"
inherit NPC;

void cinema(object tp, int num);
void cinema_mass(object tp, int num);
object ob;

void create(){
   ::create();
   set_name("The Bagman");
   set_id(({"bagman","Sevitsy","sevitsy","sevitsy the bagman","Sevitsy the Bagman","Nilith's Bagman","human"}));
   set_short("%^C100%^Se%^C101%^v%^C100%^its%^C102%^y%^C100%^, "+
   	"t%^C102%^h%^C100%^e %^C058%^B%^C059%^agm%^C058%^a%^C059%^n%^CRST%^");
   set_long("%^C100%^Wearing several layers of %^C059%^thick leather%^C100%^, "+
   	"you believe there is a %^C222%^human%^C100%^ under there but it is "+
   	"hard to tell. His form is roughly human, and when he adjusts the "+
   	"%^C241%^heavy dark cowl%^C100%^ you see %^C222%^human%^C100%^ features "+
   	"underneath. His form is average sized for a human and he bears "+
   	"no weapons but instead hefts a %^C102%^giant burlap sack%^C100%^ in "+
   	"both hands. He collects %^C243%^corpses%^C100%^ from the ruins and "+
   	"as you approach he nods and looks for you to %^C229%^>donate<%^C100%^ "+
   	"a corpse to his bag.%^CRST%^\n");
   set_weight(10000);
   set_value(5000);
   set_property("no animate",1);
   set_race("human");
   set_stats("intelligence",20);
   set_stats("wisdom",18);
   set_stats("strength",16);
   set_stats("charisma",16);
   set_stats("dexterity",12);
   set_stats("constitution",14);
   set_class("fighter");
   set_mlevel("fighter",30);
   set_guild_level("fighter",30);
   set_alignment(4);
   set_gender("male");
   set_size(2);
   set_exp(0);
   set_overall_ac(-10);
   set_hd(35,15);
   set_max_hp(400);
   set_hp(query_max_hp());
   set("aggressive",0);
   set_emotes(1, ({
"%^C100%^Sevitsy speaks in a low %^C244%^gravelly%^C100%^ voice '%^C230%^You have gift for bag? Bag always have room for gift! Just %^C153%^>donate<%^C230%^'%^CRST%^",
"%^C059%^A %^C249%^hyena%^C059%^ can be seen running through the %^C244%^ruins%^C059%^.%^CRST%^",
"%^C186%^You think you hear %^C172%^something%^C186%^ from inside of %^C058%^Sevitsy's sack%^C186%^..%^CRST%^",
}), 0);
   set_property("no bows",1);
   set_spoken("wizish");
   command("speech %^C100%^Sevitsy speaks in a low %^C244%^gravelly%^C100%^ voice");
}

void init() {
    ::init();
    add_action("sanctify_fun","donate");
}

int sanctify_fun(string str,object who){
    object ob;
    
    if(!str) {
        tell_object(TP,"%^BLACK%^%^BOLD%^Donate What?\n%^RESET%^");
        return 1;
    }

    if(str == "corpse"){
        ob=present("corpse",TP);
        if(!ob) return notify_fail("\n%^C172%^You do not have a corpse to donate.%^RESET%^\n");
        ob->remove();
        cinema(TP,0);
        return 1;
    }
	
    if((str == "mass") || (str == "mass of flesh") || (str == "tears of the lost")){
        ob=present("mass of flesh",TP);
        if(!ob) return notify_fail("\n%^C172%^You do not have a mass of flesh to donate.%^RESET%^\n");
        ob->remove();
        cinema_mass(TP,0);
        return 1;
    }

    tell_object(TP,"%^BLACK%^%^BOLD%^Donate What?\n%^RESET%^");
    return 1;
}

void cinema(object tp,int num){

    string todays_wisdom;
    string* sevitsy_wisdom = ({ "%^C230%^Bag No want child, bag wants big fat happy gift.%^RESET%^", 
    	"%^C230%^Rich, poor, they all fit in bag!","Go now sweet gift, you have work to do!%^RESET%^",
    	"%^C230%^One gift is good, find me Tears of the Lost, then we talk rewards.%^RESET%^",
    	"%^C230%^Go my friend, join the fight!%^RESET%^",
    	"%^C230%^So many gifts, such a happy bag!%^RESET%^" });
    todays_wisdom = sevitsy_wisdom[random(sizeof(sevitsy_wisdom))];

            switch(num){
                case(0):
                    tell_object(TP,"\n%^C244%^Sevitsy turns to you and you hear a deep gutteral laugh.%^RESET%^\n");
                    tell_room(ETP,"%^C244%^Sevitsy turns to "+TPQCN+" %^C244%^and laughs.%^RESET%^\n",TP);
                break;
                case(1):
                    tell_room(ETP,"%^C100%^Sevitsy speaks in a low %^C244%^gravelly%^C100%^ voice '%^C230%^You have gift for bag? Bag always have room for gift!'%^RESET%^\n",TP);                    
                break;
                case(2):
                    tell_room(ETP,""+TPQCN+" %^C106%^drops the %^C245%^corpse%^C106%^ by %^C059%^Sevitsy's%^C106%^ feet and the bagman quickly snatches it.%^CRST%^\n",TP);
                    tell_object(TP,"%^C106%^You drop the %^C244%^corpse%^C106%^ by %^C059%^Sevitsy's%^C106%^ feet and step back. He leaps forward to snatch it.%^CRST%^%^CRST%^");
                break;
                case(3):
                    tell_room(ETP,"%^C059%^Sevitsy%^C145%^ looks over the %^C244%^corpse%^C145%^, stroking it almost lovingly before unceremoniously shoving it deeply into the %^C094%^sack%^C145%^. You hear a %^C060%^horrid guttural%^C145%^ %^C167%^sucking%^C145%^ %^C060%^sound%^C145%^ from the %^C243%^depths%^C145%^ of the %^C094%^sack%^C145%^ and where it was full for a second, it is empty once again.%^CRST%^%^CRST%^\n");                break;
                case(4):
                    tell_room(ETP,"%^C100%^Sevitsy speaks in a low %^C244%^gravelly%^C100%^ voice '%^C230%^"+ todays_wisdom +"%^C100%^'%^RESET%^\n");
                break;
                case(5):
                    tell_object(TP,"%^C075%^%^C060%^Sevitsy%^C061%^ grabs a pile of %^C190%^coins%^C061%^ from his pocket and drops them at your feet.%^CRST%^%^CRST%^\n");
                    tell_room(ETP,"%^C060%^Sevitsy%^C061%^ drops a pile of %^C190%^coins%^C061%^ at %^CRST%^"+TPQCN+"%^C061%^'s feet.%^CRST%^\n",TP);
                    ob = new("/std/obj/coins");
                    ob->set_money("gold", random(100)+100);
                    ob->move(ETO);  
                    return 1;
                break;
            return;
                }
    num++;
    call_out("cinema",5,tp,num);
    return;
}

void cinema_mass(object tp,int num){
            switch(num){
                case(0):
                    tell_object(TP,"\n%^C064%^You hold out the %^C136%^mass of flesh%^C064%^ to the %^C060%^bagman%^C064%^. He looks over and almost drops his %^C094%^sack%^C064%^ with excitement.%^CRST%^\n");
                    tell_room(ETP,"\n%^C064%^As %^CRST%^"+TPQCN+"%^C064%^ holds out the %^C136%^mass of flesh%^C064%^ to %^C059%^Sevitsy%^C064%^ he almost drops his %^C094%^sack%^C064%^ in excitement.%^CRST%^\n",TP);
                break;
                case(1):
                    tell_room(ETP,"%^C100%^Sevitsy speaks in a low %^C244%^gravelly%^C100%^ voice '%^C230%^The best gift Bag is happy! I am happy!'\n",TP);        

                break;
                case(2):
                    tell_room(ETP,"Sevitsy takes the mass of flesh from "+TPQCN+" and throws back his cowl. Underneath it you see he is indeed human. He licks the soft blade of the mass and starts to chant.%^CRST%^\n",TP);
                    tell_object(TP,"Sevitsy takes the mass of flesh from you and throws back his cowl. Underneath it you see he is indeed human. He licks the soft blade of the mass and starts to chant.");              break;
                case(3):
                    tell_room(ETP,"%^C032%^The air becomes heavy with %^C056%^power%^C032%^ and the smell of %^C229%^ozone%^C032%^. You hear the yips of %^C100%^hyenas%^C032%^ in your mind and for a moment it feels like %^C229%^lightning%^C032%^ will strike all around you.%^CRST%^\n");
                break;
                case(4):
                    tell_room(ETP,"%^C067%^The %^C136%^mass of flesh%^C067%^ starts to fall apart, each %^C230%^eyeball%^C067%^ plopping softly into the %^C094%^sack%^C067%^, but alongside it you see the %^C063%^spectral images%^C067%^ of %^C194%^spirits%^C067%^ falling with it. A hundred souls falling in %^C088%^agony%^C067%^ into the maw of the %^C094%^sack%^C067%^!%^CRST%^\n");                break;
                case(5):
                    tell_room(ETP,"%^C030%^As the last of the %^C136%^mass%^C030%^ falls into the %^C094%^sack%^C030%^, you hear a %^C059%^deep grown%^C030%^ and %^C060%^Sevitsy%^C030%^ giggles. He reaches a hand into the %^C094%^sack%^C030%^ and pulls out a %^C184%^shard%^C030%^ covered in %^C088%^ichor%^C030%^.%^CRST%^\n");
                break;
                case(6):
                    tell_object(TP,"%^C060%^Sevitsy%^C071%^ wipes off the %^C088%^ichor%^C071%^ from the %^C192%^shard%^C071%^ and drops it on the ground in front of you.%^CRST%^\n");
                    tell_room(ETP,"%^C060%^Sevitsy%^C071%^ wipes the %^C088%^ichor%^C071%^ off the %^C192%^shard%^C071%^ and drops it on the ground in front of %^CRST%^"+TPQCN+"%^C071%^.%^CRST%^\n",TP);
                    ob = new(OBJ"soul_gem");
	                ob->set_short("%^C061%^c%^C075%^o%^C061%^rru%^C060%^p%^C061%^te%^C068%^d%^CRST%^ %^C184%^sha%^C193%^r%^C184%^d of d%^C193%^e%^C184%^part%^C227%^e%^C184%^d sou%^C192%^l%^C184%^s%^CRST%^");
                    ob->set_obvious_short("%^C061%^c%^C075%^o%^C061%^rru%^C060%^p%^C061%^te%^C068%^d%^CRST%^ %^C226%^gl%^C228%^o%^C226%^wi%^C192%^n%^C226%^g %^C229%^y%^C226%^ell%^C192%^o%^C226%^w %^C192%^g%^C226%^em%^CRST%^");
                    ob->move(ETO);

                break;
            return;
                }
    num++;
    call_out("cinema_mass",5,tp,num);
    return;
}



