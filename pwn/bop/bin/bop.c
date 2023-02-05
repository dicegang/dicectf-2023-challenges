#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void __attribute__((constructor)) activate_seccomp()
{
    scmp_filter_ctx ctx;
    ctx = seccomp_init(SCMP_ACT_KILL);

    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
    
    if (seccomp_load(ctx) < 0) {
        perror("seccomp_load");
        exit(EXIT_FAILURE);
    }
}

void main(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char bop[24];
    printf("Do you bop? ");
    gets(bop);
}
