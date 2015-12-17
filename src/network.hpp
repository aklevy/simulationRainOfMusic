#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <memory>
#include <functional>

#if defined(Bool)
#undef Bool
#endif
#if defined(True)
#undef True
#endif
#if defined(False)
#undef False
#endif

#include "Network/Address.h"
#include "Network/Device.h"
#include "Network/Protocol/Local.h"
#include "Network/Protocol/Minuit.h"
class network
{
public:
    network();
};

#endif // NETWORK_H
