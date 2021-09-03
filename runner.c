#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
 putenv("DISPLAY=:1");
 return execlp("/usr/bin/su","/usr/bin/su","charlie","-c","gnome-terminal",NULL);
}
