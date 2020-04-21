#include <std.h>
#include <clock.h>

inherit DISEASE;

int next_step = 0;
int saved = 0;

void create()
{
    ::create();
    set_name("mindfire");
    set_incubation("1 day");
    set_damage_desc("1d4 int");
    set_infection("inhaled");
    set_description("\n\nFeels like your brain is burning. Causes stupor.");

    set_property("inanimate bonus", 1);
    set_heart_beat(32);
}

int init_disease(int dc)
{
    ::init_disease(dc);
    next_step = ETO->query_age() + DAY;
}

advance_disease()
{
    int dmg = -roll_dice(stage, 4);

    next_step += DAY;

    if ("/daemon/saving_throw_d"->fort_save(ETO, -clevel))
    {
        tell_object(FPL("ilmarinen"),":saved:" + clevel);
        saved++;
        if (saved > 2) {
            TO->remove();
            return;
        }
        return;
    }

    set_item_bonus("intelligence",dmg);

    tell_object(ETO,"\n%^BOLD%^%^BLUE%^Your brain is burning with pain.%^RESET%^");

    stage++;

}

void heart_beat()
{
    if (!objectp(TO)) {
        return;
    }

    if (!next_step) {
        return;
    }

    if (!ETO->is_living()) {
        TO->remove();
    }
    if (ETO->query_age() > next_step) {
        advance_disease();
    }
    return;
}
