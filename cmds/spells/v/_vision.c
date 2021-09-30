inherit "/cmds/spells/c/_clairvoyance";

int clairvoyance_delay()
{
    return 60;
}

void create()
{
    ::create();
    set_spell_name("vision");
    set_spell_level(([ "mage":7, "cleric":7, "druid" : 7 ]));
    set_discipline("divination");
    set_domains(({}));
    set_syntax("cast CLASS vision on TARGET");
    set_description("This spell functions exactly like clairvoyance, except it is harder to block.");
    set_silent_casting(1);
}
