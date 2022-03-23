
//Incense Burner Master
#include <std.h>

inherit OBJECT;

//Inherit the right theater
#include "/realms/loki/theater/serakii/inn.h"

void create() {
    ::create();
    set_name("incense burner");
    set_id(({"incense","burning incense","incense burner","burner","hearthstone incense burner"}));
    set_weight(1000000);
    set_short("%^C066%^he%^C244%^a%^C066%^rth%^C244%^s%^C066%^to%^C243%^n%^C066%^e i%^C095%^n%^C066%^ce%^C094%^n%^C066%^se burn%^C094%^e%^C066%^r%^CRST%^");
    set_long("%^C059%^This %^C246%^metal bowl%^C059%^ filled with %^C095%^incense %^C059%^has been mounted on top of a small pile of %^C249%^hearth stone%^C059%^. The stone looks like the same from the %^C246%^inn %^C059%^nearby and %^C022%^ivy %^C059%^has grown up over most of it. There is a pile of %^C094%^incense%^C059%^ that has been set alight, and smoke drifts up from it slowly. You could %^C226%^inhale %^C059%^the incense to see what it smells like%^CRST%^\n");
    set_value(0);
    set_property("no animate",1);
}


void init() {
    ::init();
    add_action("inhale_show", "inhale");
}

int inhale_show(string str,object who){
    if(str == "incense" || str == "burning incense"){
        tell_object(TP,"%^C095%^you breath in the incense%^CRST%^");
        tell_room(ETP,""+TPQCN+" %^C095%^breathes in the incense%^CRST%^",TP);
		tell_a_story();
		if(member_array("Serakii_Hounds",TP->query_mini_quests())== 1) {
		tell_the_hound_version();
		}
		if(member_array("Serakii_Legion",TP->query_mini_quests())== 1) {
		tell_the_legion_version();
		}
		return 1;
	}
    tell_object(TP,"%^C095%^what are you trying to inhale?%^CRST%^\n");
	return 1;
}

void tell_a_story(int num){
 switch(num){
    case(0):tell_object(TP," "+gen1+" \n");
                        break;
    case(1):tell_object(TP," "+gen2+" \n");
                        break;
    case(2):tell_object(TP," "+gen3+" \n");
                        break;
    case(3):tell_object(TP," "+gen4+" \n");
                        break;
    case(4):tell_object(TP," "+gen5+" \n");;
                        break;

                        return;
                }

  num++;
  call_out("tell_a_story",3,num);
  return;
}

void tell_the_hound_version(int num){
 switch(num){
    case(0):tell_object(TP," "+hound1+" \n");
                        break;
    case(1):tell_object(TP," "+hound2+" \n");
                        break;
    case(2):tell_object(TP," "+hound3+" \n");
                        break;
    case(3):tell_object(TP," "+hound4+" \n");
                        break;
    case(4):tell_object(TP," "+hound5+" \n");;
                        break;

                        return;
                }

  num++;
  call_out("tell_the_hound_version",3,num);
  return;
}

void tell_the_legion_version(int num){
 switch(num){
    case(0):tell_object(TP," "+legion1+" \n");
                        break;
    case(1):tell_object(TP," "+legion2+" \n");
                        break;
    case(2):tell_object(TP," "+legion3+" \n");
                        break;
    case(3):tell_object(TP," "+legion4+" \n");
                        break;
    case(4):tell_object(TP," "+legion5+" \n");;
                        break;

                        return;
                }

  num++;
  call_out("tell_the_legion_version",3,num);
  return;
}
