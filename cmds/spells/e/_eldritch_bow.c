#include <priest.h>
#include <magic.h>
#include <spell.h>
inherit SPELL;

#define BASEDIR "/d/magic/obj/lockweapons/"

object bow;
string blasttype;

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("eldritch bow");
    set_spell_level(([ "warlock" : 1 ]));
    set_syntax("cast CLASS eldritch bow");
    set_description("A variant on the core spell-like ability of the warlock, this invocation allows "
"the caster to shape their eldritch blast into a single bow, which can be used as a melee weapon. "
"Both hands must be empty in order for this invocation to work; similarly, if a different shaped "
"blast is invoked, the bow will disappear. Releasing grip upon the weapon will end the invocation. "
"As with the eldritch blast, the bow can be imbued with various essences.\nSee also: <help "
"blasttype>.");
    set_verbal_comp();
    set_helpful_spell(1);
}

int preSpell() {
    while(present("eldritch_weapon_xxx",caster))
    {
        if(present("eldritch_weapon_xxx", caster)->query_wielded()) caster->force_me("unwield eldritch_weapon_xxx");
        if(objectp(present("eldritch_weapon_xxx", caster)))
        {
            tell_room(place,"%^RESET%^%^CYAN%^The gleaming claw shimmers and disappears.%^RESET%^");
            present("eldritch_weapon_xxx", caster)->remove();
            continue;
        }
        continue;
    }
    if(sizeof(caster->query_wielded()) > 1) {
      tell_object(caster,"You don't have any free hands!");
      return 0;
    }
    if(sizeof(caster->query_wielded()) && (caster->is_wearing_type("shield") || caster->is_wearing_type("thiefshield"))) {
      tell_object(caster,"You don't have any free hands!");
      return 0;
    }
    return 1;
}

string query_cast_string() {
    tell_object(caster,"%^MAGENTA%^You extend both hands and curl your fingers inwards.%^RESET%^");
    tell_room(place,"%^MAGENTA%^"+caster->QCN+" extends both hands and curls "+caster->QP+" fingers inwards.%^RESET%^",caster);
    return "display";
}

void spell_effect(int prof){
    string descriptor;
    string filename;

    blasttype = (string)caster->query("warlock_blast_type");
    filename = "eldritch_bow_"+blasttype;
    switch(blasttype) {
    case "frightful":
        descriptor = "%^BLUE%^ma%^MAGENTA%^l%^BLUE%^ign%^BOLD%^%^BLACK%^an%^RESET%^%^BLUE%^t e%^MAGENTA%^n%^BOLD%^%^BLACK%^e%^RESET%^%^BLUE%^r%^RESET%^g%^BLUE%^y";
        break;
    case "glacial":
        descriptor = "%^CYAN%^c%^BOLD%^%^CYAN%^r%^RESET%^%^CYAN%^a%^RESET%^ck%^BOLD%^%^BLUE%^l%^RESET%^%^CYAN%^i%^BOLD%^%^CYAN%^n%^RESET%^%^CYAN%^g e%^BOLD%^%^BLUE%^n%^BOLD%^%^CYAN%^e%^RESET%^%^CYAN%^rg%^RESET%^%^CYAN%^y";
        break;
    case "brimstone":
        descriptor = "%^RED%^s%^BOLD%^%^RED%^e%^YELLOW%^a%^RESET%^%^RED%^r%^MAGENTA%^i%^BOLD%^%^RED%^n%^RESET%^%^RED%^g e%^BOLD%^%^RED%^n%^BOLD%^%^WHITE%^e%^RESET%^%^RED%^r%^BOLD%^%^RED%^g%^RESET%^%^RED%^y";
        break;
    case "lifedrinker":
        descriptor = "%^GREEN%^s%^BOLD%^%^GREEN%^ee%^RESET%^%^GREEN%^th%^BOLD%^%^GREEN%^i%^RESET%^%^GREEN%^ng e%^BOLD%^%^GREEN%^n%^RESET%^%^GREEN%^er%^BOLD%^%^GREEN%^g%^RESET%^%^GREEN%^y";
        break;
    case "vitriolic":
        descriptor = "%^GREEN%^n%^BOLD%^%^WHITE%^o%^BOLD%^%^GREEN%^x%^RESET%^%^GREEN%^i%^CYAN%^o%^BOLD%^%^GREEN%^u%^RESET%^%^GREEN%^s e%^YELLOW%^n%^BOLD%^%^GREEN%^e%^RESET%^%^GREEN%^r%^CYAN%^g%^GREEN%^y%^RESET%^";
        break;
    case "beshadowed":
        descriptor = "%^BOLD%^%^BLACK%^te%^RESET%^n%^BOLD%^%^BLACK%^ebr%^RESET%^%^BLUE%^o%^BOLD%^%^BLACK%^us e%^RESET%^ne%^BOLD%^%^BLACK%^rgy%^RESET%^";
        break;
    case "binding":
        descriptor = "%^BOLD%^%^BLUE%^s%^BOLD%^%^WHITE%^u%^BOLD%^%^CYAN%^r%^BOLD%^%^WHITE%^g%^RESET%^%^CYAN%^i%^BOLD%^%^CYAN%^n%^BOLD%^%^GREEN%^g %^BOLD%^%^WHITE%^e%^BOLD%^%^BLUE%^n%^BOLD%^%^CYAN%^e%^BOLD%^%^WHITE%^r%^RESET%^%^CYAN%^g%^BOLD%^%^CYAN%^y%^RESET%^";
        break;
    case "utterdark":
        descriptor = "m%^BOLD%^%^BLACK%^al%^RESET%^%^MAGENTA%^ef%^RESET%^i%^MAGENTA%^c e%^BOLD%^%^BLACK%^n%^RESET%^e%^MAGENTA%^rgy";
        break;
    default:
        blasttype = "default";
        descriptor = "e%^BOLD%^%^MAGENTA%^n%^RESET%^%^MAGENTA%^e%^BOLD%^%^WHITE%^r%^BOLD%^%^MAGENTA%^g%^RESET%^%^MAGENTA%^y";
        filename = "eldritch_bow";
        break;
    }

    bow = new(BASEDIR+filename);
    bow->move(caster);
    bow->weapon_setup(caster,clevel);
    bow->set_id(({"eldritch bow","bow","energy bow","bow of energy","eldritch_weapon_xxx","%^BOLD%^%^CYAN%^b%^RESET%^%^CYAN%^ol%^BOLD%^t %^RESET%^%^CYAN%^of %^BOLD%^e%^RESET%^%^CYAN%^nerg%^BOLD%^y%^RESET%^%^CYAN%^"}));
    bow->set_short("%^RESET%^"+descriptor+"%^RESET%^ %^CYAN%^b%^BOLD%^%^CYAN%^o%^RESET%^%^CYAN%^w%^RESET%^");
    bow->set_long("%^BOLD%^%^WHITE%^This magical construct looks as though it would serve as a weapon of considerable %^RESET%^%^RED%^potency%^BOLD%^%^WHITE%^. Instead of wood or metal, however, it is made purely of "+descriptor+"%^RESET%^%^BOLD%^. Its curved like a bow, with thin, %^RESET%^%^CYAN%^translucent%^RESET%^%^BOLD%^ string connecting the arms.");
    tell_object(caster,"%^MAGENTA%^In your hands materializes a crude %^CYAN%^bow%^MAGENTA%^, formed of "+descriptor+"!%^RESET%^");
    tell_room(place,"%^MAGENTA%^In hands of "+caster->QCN+" materializes a %^CYAN%^bow%^MAGENTA%^, formed of "+descriptor+"!%^RESET%^",caster);
    caster->force_me("wield eldritch bow");

    spell_successful();
    spell_duration = (clevel + roll_dice(1, 20)) * ROUND_LENGTH * 10;
    set_end_time();
    call_out("dest_effect",spell_duration);
    return;
}

void dest_effect()
{
    if(objectp(bow))
        bow->remove();
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
