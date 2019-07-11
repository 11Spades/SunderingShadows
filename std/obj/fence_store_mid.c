// scaling the default items for thieves guilds; higher area guilds have better availabilities. N, 10/15.
#include <std.h>
#include <brewing.h>
#include <daemons.h>
inherit "std/room";

#define FENCE_D "/daemon/fence_d"
#define OKSCROLLS ({ "invisibility","clairvoyance","ice storm","tongues","shout","monster summoning 3","monster summoning 4" }) // moderate & lesser-school

int flag;
int save_contents() { return 1;}

void create() {
    ::create();
    set_properties((["light":1, "indoors":1, "no teleport":1]));
    set_properties((["storage room":1, "save contents":1]));
    set("short","A storage room for the thieves guild.");
    set("long", "Supplies and such are stored here.\n");
}

int clean_up(){ return 0;}

// stocking of the guild done here. Note: please add a relevant lantern or dark lantern depending on the location.
void reset() {
   int flag, i, val;
   object ob, *inven;
   mapping datamap;
   string elixirname;
   ::reset();

   inven = all_inventory(TO);
   if(sizeof(inven)) {
     for(i=0;i<sizeof(inven);i++) {
       if(userp(inven[i])) continue;
       inven[i]->move("/d/shadowgate/void");
       inven[i]->remove();
     }
   }

   flag = FENCE_D->restore_item(TO);
   if(--flag) FENCE_D->restore_item(TO);

   if(!present("rope")) new("/d/common/obj/misc/rope")->move(TO);
   if(!present("tools")) new("/d/common/obj/misc/thief_tools.c")->move(TO);
   if(!present("tools 2")) new("/d/common/obj/misc/thief_tools.c")->move(TO);
   if(!present("blinding powder")) new("/d/common/obj/brewing/powders/blinding_powder")->move(TO); // to replace with choking powder when installed
   if(!present("caltrops") && random(2)) new("/d/tharis/obj/caltrops")->move(TO);
   i=0;
   while(i<5) {
        i++;
        if(!present("vial "+i)) {
            ob = new ("/d/common/obj/potion/extra_heal");
            ob->set_uses(15 + random(5));
            ob->move(TO);
        }
    }
    for(i=0;i<3;i++) { // scroll time!
      if(!present("safe scroll 3")) {
        ob = new("/d/magic/safe_scroll");
        ob->set_spell_name(OKSCROLLS[random(sizeof(OKSCROLLS))]);
        ob->move(TO);
      }
    }

    if(!present("vial 6")) { // first five should be kits!
      datamap = ELIXIRS;
      switch(random(4)) {
        case 0:
          ob = new("/d/common/obj/brewing/elixirs/elixir_of_pass_without_trace");
          elixirname = "elixir of pass without trace";
        break;
        case 1:
          ob = new("/d/common/obj/brewing/elixirs/elixir_of_cats_grace");
          elixirname = "elixir of cats grace";
        break;
        case 2:
          ob = new("/d/common/obj/brewing/elixirs/elixir_of_bears_endurance");
          elixirname = "elixir of bears endurance";
        break;
        default:
          ob = new("/d/common/obj/brewing/elixirs/elixir_of_bulls_strength");
          elixirname = "elixir of bulls strength";
        break;
      }
      ob->set_myname(elixirname);
      ob->set_dc(datamap[elixirname]["dc"]);
      ob->set_strength(25);
      ob->set_hue(datamap[elixirname]["color"]);
      ob->set_value((datamap[elixirname]["value"] * roll_dice(3,4)));
      ob->move(TO);
    }

    if(!present("poison")) POISON_D->QueryPoisonObject("any", "injury")->move(TO);
    if(!present("poison 2")) POISON_D->QueryPoisonObject("any", "contact")->move(TO);

    if(!present("playersettabletrapkit")) {
      i = 2 + random(2);
      while(i) {
        ob = TRAP_D->get_trap_object("mid", "random");
        val = 300 + random(201);
        if(objectp(ob)) {
          tell_room(TO, "Trap object is valid");
          ob->move(TO);
          ob->set_value(val);
        }
        i--;
        continue;
      }
    }
}