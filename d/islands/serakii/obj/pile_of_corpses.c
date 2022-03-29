
#include <std.h>
#include "../serakii.h"

inherit OBJECT;

int how_many_corpses;
object corpse,gem;

void create() {
    ::create();
    set_name("corpses");
    set_id(({"corpses","pile","pile of corpses","large pile of corpses"}));
    set_weight(1000000);
    set_short("%^C160%^lar%^C088%^g%^C160%^e pile of c%^C088%^o%^C160%^rp%^C088%^s%^C160%^es%^CRST%^");
    set_long("%^C160%^This is a large pile of "+
        "%^C088%^children's corpses%^C160%^ that has been stacked unceremoniously. "+
        "There are a lot of them here and it is obvious that its been added to lately as "+
        "some of the %^C088%^corpses%^C160%^ are quite fresh. Though there are too many to "+
        "deal with all together you could %^C196%^>collect<%^C160%^ them one at a time.%^CRST%^\n");
    set_value(0);
    set_property("no animate",1);
    how_many_corpses = 15;
}

void init(){
   ::init();
   add_action("collect_fun","collect");
}



void collect_fun(string str){
   int roll, might, bonus;
   object obj;


   if(TP->query_bound() || TP->query_unconcious() || TP->query_paralyzed()
|| TP->query_tripped()){
      TP->send_paralyzed_message("info",TP);
      return 1;
   }
   if(!interactive(TP)) return;
   if(!str) { return 0; }
   if(str != "corpses" && str != "corpse"){
      tell_object(TP,"collect what?\n");
      return 1;
   }

    tell_object(TP,"%^C160%^You collect a single corpse from the pile.\n%^CRST%^");
    tell_room(ETP,"%^C160%^"+TPQCN+" %^C160%^pulls a corpse off the pile.\n%^CRST%^",TP);
    TP->set_paralyzed(3,"%^C058%^You are recovering from your efforts.\n%^CRST%^");

        corpse = new("/std/obj/corpse");
        corpse->set_name("human");
        corpse->set_gender(({"male","female"})[random(2)]);
        corpse->set_long("%^CYAN%^Before you is an %^CYAN%^o%^CYAN%^l%^CYAN%^d "+
         "%^CYAN%^c%^BOLD%^%^BLACK%^o%^RESET%^%^CYAN%^r%^BOLD%^%^BLACK%^"+
         "p%^RESET%^%^CYAN%^s%^CYAN%^e%^CYAN%^ of a human child in tattered "+
         "clothes. Its features are %^CYAN%^r%^BOLD%^%^BLACK%^ott%^RESET%^%^CYAN%^"+
         "e%^BOLD%^%^BLACK%^n %^BLACK%^aw%^RESET%^%^CYAN%^a%^BOLD%^%^BLACK%^"+
         "y%^RESET%^%^CYAN%^ and are hard to discern. It smells as disgustingly "+
         "as it looks, %^BOLD%^%^WHITE%^bi%^BLACK%^t%^WHITE%^s %^BLACK%^o%^WHITE%^"+
         "f %^BLACK%^b%^WHITE%^o%^BLACK%^n%^BLACK%^e%^RESET%^%^CYAN%^ peer through "+
         "decayed pieces. Who it was in life is impossible to tell at this point.");
        corpse->set__obvious_short("%^CYAN%^A child's corpse%^RESET%^");
        corpse->set_weight(20);
        corpse->move(ETP);
    how_many_corpses--;
    change_pile();
    return 1;
    }


void change_pile(){

    if(how_many_corpses > 20){
    return;
    }
    if(how_many_corpses > 10){
    set_short("%^C160%^pile of c%^C088%^o%^C160%^rp%^C088%^s%^C160%^es%^CRST%^");
    set_long("%^C160%^This is a large pile of "+
        "%^C088%^children's corpses%^C160%^ that has been stacked unceremoniously. "+
        "There are a lot of them here and it is obvious that its been added to lately as "+
        "some of the %^C088%^corpses%^C160%^ are quite fresh. Though there are too many to "+
        "deal with all together you could %^C196%^>collect<%^C160%^ them one at a time.%^CRST%^\n");
    return;
    }
    if(how_many_corpses > 1){
    set_short("%^C160%^sma%^C088%^l%^C160%^l pile of c%^C088%^o%^C160%^rp%^C088%^s%^C160%^es%^CRST%^");
    set_long("%^C160%^This is a small pile of "+
        "%^C088%^children's corpses%^C160%^ that has been stacked unceremoniously. "+
        "There are not many of them here and it is obvious that its been added to lately as "+
        "some of the %^C088%^corpses%^C160%^ are quite fresh. Though there are too many to "+
        "deal with all together you could %^C196%^>collect<%^C160%^ them one at a time.%^CRST%^\n");
    return;
}
    if(how_many_corpses==1){
    tell_room(ETP,"%^C160%^"+TPQCN+" %^C160%^only a single corpse is left.\n%^CRST%^",TP);
        corpse = new("/std/obj/corpse");
        corpse->set_name("human");
        corpse->set_gender(({"male","female"})[random(2)]);
        corpse->set_long("%^CYAN%^Before you is an %^CYAN%^o%^CYAN%^l%^CYAN%^d "+
         "%^CYAN%^c%^BOLD%^%^BLACK%^o%^RESET%^%^CYAN%^r%^BOLD%^%^BLACK%^"+
         "p%^RESET%^%^CYAN%^s%^CYAN%^e%^CYAN%^ of a human child in tattered "+
         "clothes. Its features are %^CYAN%^r%^BOLD%^%^BLACK%^ott%^RESET%^%^CYAN%^"+
         "e%^BOLD%^%^BLACK%^n %^BLACK%^aw%^RESET%^%^CYAN%^a%^BOLD%^%^BLACK%^"+
         "y%^RESET%^%^CYAN%^ and are hard to discern. It smells as disgustingly "+
         "as it looks, %^BOLD%^%^WHITE%^bi%^BLACK%^t%^WHITE%^s %^BLACK%^o%^WHITE%^"+
         "f %^BLACK%^b%^WHITE%^o%^BLACK%^n%^BLACK%^e%^RESET%^%^CYAN%^ peer through "+
         "decayed pieces. Who it was in life is impossible to tell at this point.");
        corpse->set_obvious_short("%^CYAN%^A child's corpse%^RESET%^");
        corpse->set_weight(20);
        corpse->move(ETP);

    tell_object(TP,"%^C160%^You hear the soft sigh of a child, and energy pool up around you... "+
        "Undeneath the last corpse you find a small gem has appeared.\n%^CRST%^");
    gem = new(OBJ"child_gem");
    gem->move(ETP);

    this_object()->move("/d/shadowgate/void");
    this_object()->remove();
    return;
    }




}
