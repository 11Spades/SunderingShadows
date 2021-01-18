#include <std.h>
#include <priest.h>
#include <daemons.h>

#define ALIGN_D "/daemon/alignment_d.c"

void create() {
    ::create();
    set_spell_name("detect evil");
    set_spell_level(([ "paladin" : 1 ]));
    set_spell_sphere("divination");
    set_syntax("cast CLASS detect evil on TARGET || <room>");
    set_description("Detect evil will detect the presence of evil in players or monsters.");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_non_living_ok(1);
}

int preSpell(){
    object targ;
    	if(query_arg() != 0) 
	{
    		targ = present(query_arg(), query_place());
	}
    if(!objectp(targ) && arg != "room") {
        tell_object(caster,"You need either a target or <room> for this spell.");
        return 0;
    }
//    if(!ALIGN_D->is_lawful(caster)) {
    if((int)caster->query_true_align() != 1 && (int)caster->query_true_align() != 4 && (int)caster->query_true_align() != 7 ) {
        tell_object(caster,"Only casters of good alignment may use this spell.");
        return 0;
    }
    return 1;
}

string query_cast_string() 
{
   return ""+YOU+" focuses on "+MINE+" holy symbol and chants softly.\n";
}

void spell_effect(int prof) 
{
    string arg;
    int i, hits = 0;
    object *alive,ob;

    arg = caster->realName(arg);
    if(arg == "") arg = ARG;
    if(arg == "room") {
        alive = all_living(environment(CASTER));
        alive -= ({CASTER});
        for (i=0;i<sizeof(alive);i++) {
            if(alive[i]->query_invis()) continue;
            hits++;
            if (ALIGN->is_evil(alive[i])) 
            {
                tell_object(CASTER,"%^BOLD%^%^RED%^You detect evil in "+alive[i]->QCN+".");
            }else {
                tell_object(CASTER,"%^BOLD%^%^BLUE%^You detect no evil in "+alive[i]->QCN+".");
           }
        }
        if(!hits)
        {
            tell_object(CASTER, "%^BOLD%^%^BLUE%^You detect no evil.%^RESET%^");
        }
    } 
    else if (!ob = present(arg,environment(caster))) 
    {
        tell_object(CASTER,"That is not here.");
        dest_effect();
        return;
    } 
    else if (!living(ob)) 
    {
        tell_object(CASTER,"You can't detect evil in that.");
        dest_effect();
        return;
    } 
    else 
    {
        if (ALIGN->is_evil(ob)) 
        {
            tell_object(CASTER, "%^BOLD%^%^RED%^You detect evil in "+ob->QCN+".");
        } 
        else 
        {
            tell_object(CASTER,"%^BOLD%^%^BLUE%^You detect no evil in "+ob->QCN+".");
        }
    }
    spell_successful();
    dest_effect();
}


void dest_effect() 
{
    ::dest_effect();
    if(objectp(TO)) TO->remove();

}
