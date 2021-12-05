
//Incense White Tower
#include <std.h>

inherit OBJECT;

//Inherit the right theater
#include "/realms/loki/theater/serakii/white.h"

void create() {
    ::create();
    set_name("incense burner");
    set_id(({"incense","burning incense","incense burner"}));
    set_weight(1000000);
    set_short("inn incense");
    set_long("Incense Thingy.\n");
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
