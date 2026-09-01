#include <stdio.h>

int main(int argc, char** argv) {
    int n;

    FILE* f = popen("who | sed -E 's/ .*//'|sort|uniq|wc -l", "r");
    fscanf(f, "%d", &n);
    pclose(f);
    printf("%d utilizatori\n", n);
    (void)argc;
    (void)argv;
    return 0;
}
