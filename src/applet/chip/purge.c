#include "purge.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <main.h>

#include <euicc/es10c.h>

static int applet_main(int argc, char **argv)
{
    int ret;

    if (argc < 2)
    {
        printlnf("Usage: %s [yes|other]", argv[0]);
        printlnf("\t\tConfirm purge eUICC, all data will lost!");
        return -1;
    }

    if (strcmp(argv[1], "yes") != 0)
    {
        printlnf("Purge canceled");
        return -1;
    }

    if ((ret = es10c_euicc_memory_reset(&euicc_ctx)))
    {
        const char *reason;
        switch (ret)
        {
        case 1:
            reason = "nothing to delete";
            break;
        default:
            reason = "unknown";
            break;
        }
        jprint_error("es10c_euicc_memory_reset", reason);
        return -1;
    }

    jprint_success(NULL);

    return 0;
}

struct applet_entry applet_chip_purge = {
    .name = "purge",
    .main = applet_main,
};
