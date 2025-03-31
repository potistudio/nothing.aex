#include "AEConfig.h"
#include "AE_EffectVers.h"

#ifndef AE_OS_WIN
    #include <AE_General.r>
#endif

resource 'PiPL' (16000) {
    {
        Kind { AEEffect },
        Name { "nothing" },
        Category { "POTI" },

        #ifdef AE_OS_WIN
            #ifdef AE_PROC_INTELx64
                CodeWin64X86 { "EffectMain" },
            #endif
        #else
            #ifdef AE_OS_MAC
                CodeMacIntel64 { "EffectMain" },
                CodeMacARM64 { "EffectMain" },
            #endif
        #endif

        AE_PiPL_Version { 2, 0 },
        AE_Effect_Spec_Version { PF_PLUG_IN_VERSION, PF_PLUG_IN_SUBVERS },
        AE_Effect_Version { 591361 },
        AE_Effect_Info_Flags { 0 },
        AE_Effect_Global_OutFlags { 0x02000000 },
        AE_Effect_Global_OutFlags_2 { 0x08000000 },
        AE_Effect_Match_Name { "POTI nothing" },
        AE_Reserved_Info { 0 },
        AE_Effect_Support_URL { "https://github.com/potistudio" }
    }
};
