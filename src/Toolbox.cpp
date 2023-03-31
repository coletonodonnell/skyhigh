#include "Toolbox.h"

Toolbox::Toolbox()
{
    // put the airport shit in here
}

// https://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html
Toolbox& Toolbox::getInstance()
{
    static Toolbox tb;
    return tb;
}