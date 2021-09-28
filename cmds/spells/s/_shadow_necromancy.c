inherit "/cmds/spells/s/_shadow_evocation";

void create()
{
    ::create();
    set_spell_name("shadow necromancy");
    set_spell_level(([ "mage" : 4, "innate":4, "oracle" : 4]));
    set_mystery("shadow");
    set_spell_sphere("illusion");
    set_syntax("cast CLASS shadow necromancy on SPELL_NAME [on SPELL_ARGS]");
    set_description("You create an illusory version of a necromancy spell of 3rd level or lower. The source of the illusion can differ based on the caster.

%^BOLD%^%^RED%^E.G.%^RESET%^ <cast mage shadow necromancy on vampiric touch on goblin>");
    set_arg_needed(1);
}

string shadow_school()
{
    return "necromancy";
}
