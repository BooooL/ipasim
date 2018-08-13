// dyld.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

using namespace llvm;
using namespace MachO;
using namespace std;

void _dyld_initialize(const mach_header* mh) {
    // Find all `LC_LOAD_DYLIB` commands.
    auto cmd = reinterpret_cast<const load_command *>(mh + 1);
    for (size_t i = 0; i != mh->ncmds; ++i) {
        if (cmd->cmd == LC_LOAD_DYLIB) {
            auto dylib = reinterpret_cast<const dylib_command *>(cmd);

            // Just log its name for now.
            auto name = reinterpret_cast<const char *>(dylib) + dylib->dylib.name;
            cout << name << endl;
        }

        // Move to the next `load_command`.
        cmd = reinterpret_cast<const load_command *>(reinterpret_cast<const uint8_t *>(cmd) + cmd->cmdsize);
    }
}
