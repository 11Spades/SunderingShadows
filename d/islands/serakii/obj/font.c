// Lysara's Font - Serakii - Commissioned by Malcolm and Sophia - LoKi 2022	

#include <std.h>
#include "../serakii.h"
inherit OBJECT;

void cinema(object tp, int num);

void create(){
    ::create();
    set_name("Lysara's Font");
    set_id(({"font","lysara's font","fountain"
,"altar","stone font","stone shrine","shrine"}));
    set_short("%^C059%^sto%^C246%^n%^C059%^e "+
    	"shri%^C246%^n%^C059%^e%^CRST%^");
    set_long("This %^C060%^shrine%^CRST%^ consists of a %^C243%^small stone "+
    	"bowl%^CRST%^ of %^C075%^water%^CRST%^ sitting to the side of a %^C243%^slab "+
    	"of rock%^CRST%^ the size of a small bed. The %^C244%^stone%^CRST%^ has "+
    	"been smoothed to an almost %^C152%^glass%^CRST%^ like texture and "+
    	"stands in contrast to the %^C239%^ruins%^CRST%^ around it. Along "+
    	"the %^C245%^slab%^CRST%^ is %^C060%^writing%^CRST%^ that you could %^C074%^>read<%^CRST%^. "+
    	"The %^C243%^stone bowl%^CRST%^ seems to be constantly filled "+
    	"with %^C075%^water%^CRST%^ though you are unsure how. The %^C060%^whole "+
    	"shrine%^CRST%^ seems to %^C195%^radiate%^CRST%^ %^C081%^calm%^CRST%^ "+
    	"and %^C068%^peace%^CRST%^.%^RESET%^");
    set_weight(10000);
    set_value(5000);
    set_property("no animate",1);
}

void init() {
    ::init();
    add_action("read_fun", "read");
    add_action("sanctify_fun","sanctify");
}

int read_fun(string str,object who){

    if(!str) {
       tell_object(TP,"%^BLACK%^%^BOLD%^Read what?\n%^RESET%^");
       return 1;
    }

    if((str == "writing") || (str == "shrine")){
        tell_object(TP,"%^RED%^%^C059%^you read the text around the stone "+
        "slab..\n%^CRST%^\n %^C081%^May the light of She who Sees Beyond light "+
        "your path and light this blighted land. Do not fear death but "+
        "instead celebrate life and its mysteries. For each poor soul "+
        "you %^C062%^>sanctify<%^C081%^ here on Lysara's Font they are placed on the "+
        "path to her light and the mysteries beyond.%^CRST%^\n");
        tell_room(ETP,""+TPQCN+" reads the writing.",TP);

       return 1;
    }
    return 0;
}

int sanctify_fun(string str,object who){
    object ob;
    
    if(!str) {
        tell_object(TP,"%^BLACK%^%^BOLD%^Sanctify What?\n%^RESET%^");
        return 1;
    }

    if(str == "corpse"){
        ob=present("corpse",TP);
        if(!ob) return notify_fail("\nYou do not have a corpse to sanctify.\n");
        ob->remove();
        cinema(TP,0);
        return 1;
    }

    tell_object(TP,"%^BLACK%^%^BOLD%^Sanctify What?\n%^RESET%^");
    return 1;
}

void cinema(object tp,int num){
            switch(num){
                case(0):
                    tell_object(TP,"\n%^C152%^You place the %^C088%^corpse%^C152%^ on "+
                    	"the %^C245%^slab%^C152%^, carefully arranging it as best "+
                    	"you can.%^CRST%^\n");
                    tell_room(ETP,"%^C152%^\n%^CRST%^"+TPQCN+"%^C152%^ places a %^C088%^corpse%^C152%^ "+
                    	"on the %^C244%^slab%^C152%^, seeming to carefully arrange it.%^CRST%^\n",TP);
                break;
                case(1):
                    tell_object(TP,"%^C109%^Taking a small amount of %^C075%^water%^C109%^ "+
                    	"from the %^C245%^stone bowl%^C109%^ in your palm, you drip "+
                    	"it on the %^C088%^corpse%^C109%^ and whisper a short prayer%^CRST%^\n");
                    tell_room(ETP,"%^C109%^Reaching over to the %^C246%^small bowl%^C109%^ "+
                    	"of %^C075%^water%^C109%^,%^CRST%^ "+TPQCN+" %^C109%^takes some "+
                    	"in their hand and drips it on the corpse. They whisper a short prayer.%^CRST%^\n",TP);                    
                break;
                case(2):
                    tell_room(ETP,""+TPQCN+" %^C066%^steps back from the %^C244%^slab%^C066%^ "+
                    	"and closes their eyes a moment.%^CRST%^\n",TP);
                    tell_object(TP,"%^C066%^You close your eyes as you finish your "+
                    	"prayer, hoping something can hear it.%^CRST%^");
                break;
                case(3):
                    tell_room(ETP,"%^C246%^You hear the %^C249%^sharp caw%^C246%^ "+
                    	"of a %^C238%^raven%^C246%^ echo through the ruins of the "+
                    	"city.%^CRST%^\n");
                break;
                case(4):
                    tell_room(ETP,"%^C153%^Soft whispers can be heard and you watch "+
                    	"a %^C152%^soft outline%^C153%^ of something rise from the "+
                    	"corpse, then it quickly disapates into the breeze. The corpse "+
                    	"itself seems to disolve into dust that floats away as well%^CRST%^\n");
                break;
                case(5):
                    tell_object(TP,"%^C075%^You hear a whisper of thanks, and a "+
                    	"sense that a %^C073%^soul%^C075%^ is at rest...%^CRST%^\n");
                break;
            return;
                }
    num++;
    call_out("cinema",5,tp,num);
    return;
}















