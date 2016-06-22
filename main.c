/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Pticon wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_CMD         1024


#ifdef DEBUG
# define DBG(...)       fprintf(stderr, __VA_ARGS__)
#else /* DEBUG */
# define DBG(...)
#endif /* DEBUG */


static int set_cmd ( const int argc, const char * const argv[], char * cmd, const size_t cmdlen )
{
    size_t          i;
    size_t          len;

    if ( argc <= 0 )
        return -1;

    for ( i = len = 0 ; i < argc ; i++ )
        len += snprintf ( cmd + len, cmdlen - len, "%s ", argv [i] );

    return 0;
}

int main ( int argc, char *argv [] )
{
    char             cmd [MAX_CMD] = { 0 };

    if ( setuid ( 0 ) || setgid ( 0 ) )
        return -1;

    argc--, argv++;

    if ( set_cmd ( argc, (const char * const *) argv, cmd, sizeof ( cmd ) ) )
        return -1;

    return system ( cmd );
}
