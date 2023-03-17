#include <cstdint>
#include <unordered_map>
#include <MinHook.h>

namespace MHook {
    using std::uintptr_t;

    inline std::unordered_map<void*, void*> hooks;

    auto registerHook(uintptr_t address, void* hook) {
        void* trampoline;
        auto status = MH_CreateHook(reinterpret_cast<void**>(address), hook, &trampoline);
        if (status == MH_OK)
            hooks[hook] = trampoline;
        else if(MessageBoxA(nullptr, "An error has occured while hooking a function...\n\nThis is likely caused by an outdated version of \"minhook.x86.dll\".\nWould you like to open the download page and get the updated version?\n\nFix tutorial:\n1) Download minhook.x86.dll from this page\n2) Put it in your GD folder", "BetterInfo - Geometry Dash", MB_ICONERROR | MB_YESNO) == IDYES) system("explorer https://github.com/HJfod/minhook/releases/latest");
        return status;
    }

    template <typename F>
    inline auto getOriginal(F self) {
        return reinterpret_cast<F>(hooks[self]);
    }
}

#define CC_HOOK(symbol, hook, orig) MH_CreateHook((PVOID)((int)GetProcAddress(GetModuleHandle("libcocos2d.dll"), symbol)), hook, (PVOID*)&orig)
#define HOOK(addr, hook, orig) MH_CreateHook((PVOID)(gd::base + addr), hook, (LPVOID*)&orig)

