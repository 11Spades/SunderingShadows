inherit "/std/armour";

void create() {
    ::create();
    set_name("sshield");
    set("id", ({ "shield","small shield", "small" }) );
    set("short", "A small shield.");
    set("long", 
	"This shield is made of leather, hardened in boiling oil and then "
	"shaped into an oval shield."
       );
    set_weight(5);
    set("value", 3);
    set_type("shield");
    set_limbs( ({ "right hand","left hand" }) );
    set_ac(1);
}
