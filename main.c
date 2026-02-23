#include "pal.h"
#include "bootscreen.h"
#include "user.h"
#include "installer.h"
#include "prompt.h"

int main()
{
    pal_init();
    bootscreen_show(0);   /* generic OE bootscreen */

    if (user_exists())
        login();
    else
        installer_prompt(0);   /* first-time setup */

    return 0;
}