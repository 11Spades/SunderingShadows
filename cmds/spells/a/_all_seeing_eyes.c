#include <std.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

int theProf;

void create() {
    ::create();
    set_spell_name("all seeing eyes");
    set_spell_level(([ "warlock" : 1 ]));
    set_spell_sphere("alteration");
    set_syntax("cast CLASS all seeing eyes");
    set_description("This will give the warlock the ability to understand any mortal language. You will be able to speak in a way that you'll be understood by any being. This will not alter your knowledge and won't allow you to teach or write in languages you don't know.");
    set_verbal_comp();
	set_helpful_spell(1);
    set_feats_required(([ "warlock" : "tome of ancient secrets"]));
}

int preSpell()
{
    if(caster->query_property("verstandnis"))
    {
        tell_object(caster,"You are already under the influence of similar magic");
        return 0;
    }
    return 1;
}

string query_cast_string()
{
   return "%^RESET%^%^CRST%^%^C202%^"+caster->query_cap_name()+"%^RESET%^%^CRST%^%^C202%^ calls upon strange and forbidden %^C214%^kn%^C220%^o%^C226%^wle%^C220%^d%^C214%^ge%^C202%^.%^CRST%^";
}

void spell_effect(int prof) {
    int i;
    string what, arg;
    object ob;

    tell_object(caster, "%^RESET%^%^CRST%^%^C202%^You imbue yourself with the %^C214%^kn%^C220%^o%^C226%^wle%^C220%^d%^C214%^ge %^RESET%^%^C202%^to understand all %^C214%^t%^C220%^o%^C226%^ngu%^C220%^e%^C214%^s%^C202%^.%^CRST%^");

    caster->set_property("verstandnis",1);

    addSpellToCaster();
    spell_successful();
    caster->set_property("spelled",({TO}));
    spell_duration = (clevel + roll_dice(1, 20)) * ROUND_LENGTH * 5;
    set_end_time();
    call_out("dest_effect",spell_duration);
}

void dest_effect() {
    int i;
    if (objectp(caster)) {
        caster->set_property("verstandnis",-1);
        tell_object(caster, "%^RESET%^%^CRST%^%^C202%^The %^C214%^kn%^C220%^o%^C226%^wle%^C220%^d%^C214%^ge %^RESET%^%^C202%^to understand all %^C214%^t%^C220%^o%^C226%^ngu%^C220%^e%^C214%^s%^C202%^ leaves your mind.%^CRST%^");
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

void do_spell_blowup(int prof){ MAGIC_D->fizzile(TO); }
