#include <stdio.h>
#include <regex.h>
 
#define PATTERN "^[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}$"
#define STRING "127.0.0.1.67.67.67.67.67.67.67"
 
int main() {
    regex_t preg;
    int err,regerr;
    err = regcomp (&preg, PATTERN, REG_EXTENDED);
    if (err != 0) {
        char buff[512];
        regerror(err, &preg, buff, sizeof(buff));
        printf("%s",buff);
    }
 
    regmatch_t pm;
    regerr = regexec (&preg, STRING, 0, &pm, 0);
    if (regerr == 0) printf("true"); else {
    printf("false\n");
    char errbuf[512];
    regerror(regerr, &preg, errbuf, sizeof(errbuf));
    printf("%s",errbuf);
    }
    return 0;
}

