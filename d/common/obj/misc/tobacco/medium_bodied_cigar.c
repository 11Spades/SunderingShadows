#include <std.h>
#include <move.h>
inherit "/d/common/obj/misc/tobacco/cigar.c";

void create()
{
    ::create();
    set_name("cigar");
    set_id(({ "cigar", "medium cigar", "medium bodied cigar", "medium-bodied cigar" }));
    set_short("%^CRST%^%^RESET%^%^C101%^a medium-bodied cigar%^CRST%^");
    set_long("%^CRST%^%^RESET%^%^C101%^This is a hand rolled cigar measuring approximately five and a half inches long by just over half an inch wide, in the shape commonly called a corona. Bundled, flue-cured leaves make up the filler of this cigar, while a perfect, %^C095%^reddish-brown leaf%^RESET%^%^C101%^ has been used as the wrapper. The cigar itself smells of %^C136%^cedar%^C101%^, %^C137%^cream%^C101%^ and %^C102%^rich %^C100%^tobacco%^RESET%^%^C101%^.%^CRST%^\n\n%^C130%^Try smoking it. Douse it to put it out.%^CRST%^");
    lit = 0;
    hasmsgs = 1;
    tracker = 0;
    mymsgs = ({ "%^RESET%^%^CRST%^%^C101%^You enjoy the %^C102%^pungent%^C101%^, yet not overpowering, taste of the %^C100%^t%^C101%^o%^C102%^b%^C100%^ac%^C101%^c%^C100%^o%^RESET%^%^C101%^.%^CRST%^"});
    yourmsgs = ({"%^CRST%^%^RESET%^%^C103%^You smell an %^C243%^a%^C244%^r%^C245%^o%^C246%^m%^C243%^a%^RESET%^%^C103%^ of burning %^C100%^t%^C101%^o%^C102%^b%^C100%^ac%^C101%^c%^C100%^o%^RESET%^%^C103%^.%^CRST%^"});
    intox = 0;
}
