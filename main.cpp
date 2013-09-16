// global configuration
#include "config.h"

// system includes
#include <stdint.h>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

// package includes
#include "main.h"
#include "schedule.h"

int main(int argc, char **argv)
{
    // portablity issue
    signal(SIGINT, sigint_handler);
    using namespace Simulator;

    return 0;
}

void sigint_handler(int param)
{
    std::exit(0);
}
