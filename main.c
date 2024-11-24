#include "stego.h"

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        writeMsg(argc, argv);
    }
    else
    {
        readMsg(argc, argv);
    }
}
