#include <std.h>
#include "../tormdefs.h"

inherit whatever;

void create() {
  ::create();
   set_terrain(CITY);
   set_travel(PAVED_ROAD);
  set_short("Dock road");
  set_long( "Dock road.\n"
    "  Dock road continues north and south towards the center of Torm."
    "  To the east a %^BOLD%^%^CYAN%^sign %^RESET%^hangs next to the door of the small building to the east, declaring the name of the establishment '%^BOLD%^%^CYAN%^Mirror, Mirror%^RESET%^.  The sign bears depictions of a pair of scissors and a mirror."
    "  To the west is the wall around Torm's central park."
    "  Straight south of here is the eastern edge of the city market."
  );
  set("night long",
  "%^BLUE%^Dock road is covered in a light fog.  The wall around Torm's park"+
  " to the west extends above the fog, giving you a better idea of"+
  " where you are. A %^BOLD%^%^CYAN%^sign %^RESET%^%^BLUE%^hangs next to the door of the small building to the east, declaring the name of the establishment '%^BOLD%^%^CYAN%^Mirror, Mirror%^RESET%^'. %^RESET%^%^BLUE%^ The sign bears depictions of a pair of scissors and a mirror. A light fog has settled over the rest of the city, but the "
   "%^YELLOW%^light %^RESET%^%^BLUE%^from the shop to the east %^RESET%^%^BLUE%^seems to chase it away here."
  );
  set_exits(([
  "north":TCITY+"c14",
  //"east": "/d/player_houses/gwenhwyfar/salon_main.c",
  "south":TCITY+"c35",
  ]));
}
