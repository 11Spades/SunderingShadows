#include <std.h>

int cmd_wizlog(string str)
{

    string * args, arg;
    string name;
    int bytes = 2048;

    if (!sizeof(str)) {
        tell_object(TP, "Provide name of a wiz as an argument, at least.");
    }

    args = explode(str, " ");

    foreach(arg in args)
    {
        if (regexp(arg, "[0-9]+")) {
            bytes = atoi(arg);
        }else {
            name = arg;
        }
    }

    bytes = (bytes > 10 * 1024) ? (10 * 1024) : bytes;

    tail("/log/tshlog/wizard/"+name, 2048);
    return 1;
}

void help(){
  write(
"
%^CYAN%^NAME%^RESET%^

wizlog - review activity of creators and above

%^CYAN%^SYNTAX%^RESET%^

wizlog %^ORANGE%^%^ULINE%^NAME%^RESET%^ [%^ORANGE%^%^ULINE%^BYTES%^RESET%^]

%^CYAN%^DESCRIPTION%^RESET%^

To increase transparency, this command will display recent command history typed in by a wizard with the %^ORANGE%^%^ULINE%^NAME%^RESET%^. This command won't display activity of avatars. It only affects conduct of wizards, your coder and administration stuff. Please consider applying to become one and help the mud!

Optional byes argument will display last %^ORANGE%^%^ULINE%^BYTES%^RESET%^ of the file. Default is 2048. If you want to see more and historical data, refer to logs published on the website:

  %^ULINE%^%^BLUE%^https://shadowgate.org/files/wizlog/%^RESET%^

%^CYAN%^SEE ALSO%^RESET%^

help, help *player commands
"
	);
}
