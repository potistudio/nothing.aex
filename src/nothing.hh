#pragma once

#include <iostream>


//* Include AE *//
#include "AEConfig.h"

#ifdef AE_OS_WIN
	typedef unsigned short PixelType;
	#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"
#include "AE_EffectCBSuites.h"
#include "AEGP_SuiteHandler.h"


//* Versioning *//
#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define BUG_VERSION   0
#define STAGE_VERSION PF_Stage_RELEASE
#define BUILD_VERSION 0


//* Extern *//
extern "C" {
	DllExport PF_Err EffectMain (
		PF_Cmd         cmd,
		PF_InData      *in_data,
		PF_OutData     *out_data,
		PF_ParamDef    *params[],
		PF_LayerDef    *output,
		void           *extra
	);
}
