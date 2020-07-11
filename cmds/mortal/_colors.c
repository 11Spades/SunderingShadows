#include <std.h>

int help(string str);

int cmd_colors(string str)
{
    string command,color;

    if(!stringp(str) || str == "" || str == " ") { return help(str); }

    if(sscanf(str,"start %s",command) == 1) { str = "start"; }
    if(sscanf(str,"end %s",command) == 1) { str = "end"; }

    switch(str)
    {
    case "start":

        tell_object(TP,"Setting start color for emote speech to: "+command+" this color");
        TP->set("start_color",command);
        return 1;

    case "end":

        tell_object(TP,"Setting end color for emote speech to: "+command+" this color");
        TP->set("end_color",command);
        return 1;

    default: return help(str);
    }
    
    return 0;
}

void help()
{

    write("
%^CYAN%^NAME%^RESET%^

colors - set color of direct speech

%^CYAN%^SYNOPSIS%^RESET%^

colors start|end COLOR

%^CYAN%^DESCRIPTION%^RESET%^

This command will set color of direct speech inside of emotes. You can have only one direct speech within single emote.

For example, <color start %%%^^^CYAN%%%^^^> followed by <color start %%%^^^RED%%%^^^> will make your emote

    <emoteat TARGET $M pokes $N gently, \"Hey you\", then snickers.> 

appear as 

    Yourname pokes Someone gently, %^CYAN%^\"Hey you\"%^RED%^, then snickers.%^RESET%^

%^CYAN%^SEE ALSO%^RESET%^

color, emote, emoteat

");
}
