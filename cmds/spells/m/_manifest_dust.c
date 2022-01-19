#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;

#define DELAY 5000

void create()
{
    ::create();
    set_spell_name("manifest dust");
    set_spell_level(([ "innate" : 9 ]));
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS manifest dust");
    set_save("will");
    set_description("The feyborn creates a small amount of faery dust.");
    set_verbal_comp();
    set_somatic_comp();
}

string query_cast_string()
{
	tell_object(caster,"%^C061%^You pull out a small leather pouch and blow a small amount of magical dust into it!");
    tell_room(caster,"%^C061%^" + caster->QCN+" pulls out a small %^C058%^leather %^C061%^pouch as "+caster->QP+" blows a bit of %^C129%^faery dust %^C061%^into it.%^RESET%^");
	return "display";
}
int preSpell(){
   if((int)caster->query_property("fey power")+DELAY > time()){
      tell_object(caster,"%^C061%^You do not have enough fey energy built up yet.");
      return 0;
   }
   return 1;
}
void spell_effect(int prof)
{
	object obj;
	obj=new("/realms/klieth/spells/faery_dust.c");
	obj->move(caster);
	caster->set_property("fey power",TO);
   caster->set_property("spelled", ({TO}));
   addSpellToCaster();
   spell_successful();

}

void dest_effect(){

    if(objectp(caster)) caster->remove_property("fey power");
    ::dest_effect();
}
