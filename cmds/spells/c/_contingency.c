#include <spell.h>
#include <magic.h>
#include <daemons.h>

inherit SPELL;
object cont;

void create() {
  ::create();
    set_spell_name("contingency");
    set_spell_level(([ "mage" : 6 ]));
    set_spell_sphere("invocation_evocation");
    set_syntax("cast CLASS contingency on SPELL_NAME [on SPELL_ARGS]");
    set_description("This spell allows you to put a spell in reserve, and call upon it at any time with the command <now>. The target of the reserved spell is always the caster, but arguments can be specified for spells that require them. You must carry a likeness of yourself, usually a small statue, when casting this spell. The likeness can not hold psionic powers, monk ki or warlock invocations.

Example of usage:  cast contingency on teleport on LOCATION");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_casting_time(2);
}

string query_cast_string() {
  return caster->QCN+" throws whispers silently then starts another spell.";
}

int preSpell() {
  if (!present("statue of "+capitalize(caster->query_name()),caster)) {
    tell_object(caster,"You need to have a likeness of yourself to cast upon.");
    return 0;
  }
  if(present("remotexoli", caster)){
      message("info", "You already have a contingency in place.", caster);
      return 0;
  }
  return 1;
}

void spell_effect(int prof) {
  string spell, args, *comp_names, orgSpell, newtype, myclass, improv;
  int x, spellProf, spelllevel, i;
  object spellObj;


  if (!ARG) {
    dest_effect();
    return;
  }

  if (sscanf(ARG,"%s on %s",spell,args) != 2) {
    spell = ARG;
    args = 0;
  }

  orgSpell = spell;

  spell = replace_string(spell," ","_");
  spell = "/cmds/spells/"+spell[0..0]+"/_"+spell;
  if (!file_exists(spell+".c")) {
    tell_object(caster,"That spell does not exist.");
    dest_effect();
    return;
  }

  foreach(myclass in caster->query_classes()) {
      if (myclass == "monk" || myclass == "warlock" || myclass == "psion" || myclass == "psywarrior") continue;
      newtype = myclass;
      if (newtype == "bard" || newtype == "sorcerer" || newtype == "oracle" || newtype == "magus" || newtype == "inquisitor") {
        improv = "level " + spell->query_spell_level(newtype);
        if (caster->can_memorize(newtype, improv) && member_array(orgSpell, caster->query_mastered_spells(newtype)) != -1) {
          orgSpell = improv;
          break;
        }
      }
      if (caster->can_memorize(newtype, orgSpell)) {
        break;
      }
      newtype = spell_type;
  }

  if (!caster->query_memorized(newtype,orgSpell)) {
    tell_object(caster,"You cannot cast that spell.");
    dest_effect();
    return;
  }

  if (stringp(args) && !spell->query_arg_needed()) {
    args = 0;
  }

  caster->forget_memorized(newtype,orgSpell);
  caster->set_property("spelled",({TO}));
  cont= new("/d/magic/obj/contingency");

  cont->set_clevel(clevel);
  cont->set_spell(spell);
  cont->set_spell_type(newtype);
  cont->set_args(args);
  cont->move(caster);
  tell_room(place,"%^BOLD%^%^RED%^You hear a sucking noise in the background as if some magic has been sucked into a bottle.");
  tell_object(caster,"Type, <now> to activate");
  set_heart_beat(1);
  spell_successful();
  addSpellToCaster();
}

void dest_effect(){
  if (objectp(cont)) {
    tell_room(environment(caster),"%^BOLD%^%^RED%^You hear a slight pop and crackle.");
    cont->remove(0);
  }
  if (!objectp(caster)) {
    remove();
    return;
  }
  caster->remove_property_value("spelled", ({TO}) );
  removeSpellFromCaster();
  ::dest_effect();
  if(objectp(TO)) TO->remove();
}

void heart_beat() {
  //  ::heart_beat();
  if (!objectp(cont)){
    if(objectp(TO)) TO->dest_effect();
  }
}
