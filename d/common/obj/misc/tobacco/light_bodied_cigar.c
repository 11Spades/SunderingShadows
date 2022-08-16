#include <std.h>
#include <move.h>
inherit "/d/common/obj/misc/tobacco/cigar.c";

void create()
{
    ::create();
    set_name("cigar");
    set_id(({ "cigar", "light cigar", "light bodied cigar", "light-bodied cigar" }));
    set_short("%^CRST%^%^RESET%^%^C101%^a light-bodied cigar%^CRST%^");
    set_long("%^CRST%^%^RESET%^%^C101%^This is a hand rolled cigar measuring approximately five and a half inches long by just over half an inch wide, in the shape commonly called a corona. Bundled, flue-cured leaves make up the filler of this cigar, while a perfect, %^C094%^light tan leaf%^C101%^ has been used as the wrapper. The cigar itself smells of %^C136%^oak%^C101%^, %^C137%^cream%^C101%^ and %^C102%^lightly fired %^C100%^tobacco.%^RESET%^\n\n%^C130%^Try smoking it. Douse it to put it out.%^CRST%^");
    lit = 0;
    hasmsgs = 1;
    tracker = 0;
    mymsgs = ({ "%^RESET%^%^CRST%^%^C101%^You enjoy the %^C102%^light%^C101%^ and %^C102%^creamy%^C101%^ taste of the %^C100%^t%^C101%^o%^C102%^b%^C100%^ac%^C101%^c%^C100%^o%^RESET%^%^C094%^.%^CRST%^"});
    yourmsgs = ({"%^CRST%^%^RESET%^%^C103%^You smell a %^C243%^m%^C244%^i%^C245%^l%^C246%^d %^C243%^a%^C244%^r%^C245%^o%^C246%^m%^C243%^a%^RESET%^%^C103%^ of burning %^C100%^t%^C101%^o%^C102%^b%^C100%^ac%^C101%^c%^C100%^o%^RESET%^%^C103%^.%^CRST%^"});
    intox = 0;
}
