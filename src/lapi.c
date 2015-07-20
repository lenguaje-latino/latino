
static void fatal_error(const char *msg)
{
    (void) fprintf(stderr, "%s\n", msg);
    exit (EXIT_FAILURE);
}

