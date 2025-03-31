#include "./nothing.hh"


static PF_Err About (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	// do something

	return error;
}


static PF_Err GlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	// do something

	return error;
}


static PF_Err ParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	// do something

	return error;
}


static PF_Err Render (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	// do something

	return error;
}


//* Resources *//

extern "C" {
	DllExport PF_Err PluginDataEntryFunction2 (PF_PluginDataPtr inPtr, PF_PluginDataCB2 inPluginDataCallBackPtr, SPBasicSuite *inSPBasicSuitePtr, const char *inHostName, const char *inHostVersion) {
		PF_Err result = PF_Err_INVALID_CALLBACK;

		result = PF_REGISTER_EFFECT_EXT2 (
			inPtr,
			inPluginDataCallBackPtr,
			"",
			"POTI ",
			"POTI",
			AE_RESERVED_INFO,
			"EffectMain",
			"https://github.com/potistudio"
		);

		return result;
	}
}


//* Extern *//

PF_Err EffectMain (PF_Cmd cmd, PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output, void *extra) {
	PF_Err error = PF_Err_NONE;

	try {
	switch (cmd) {
		case PF_Cmd_ABOUT:
			error = About (in_data, out_data, params, output);
			break;
		case PF_Cmd_GLOBAL_SETUP:
			error = GlobalSetup (in_data, out_data, params, output);
			break;
		case PF_Cmd_PARAMS_SETUP:
			error = ParamsSetup (in_data, out_data, params, output);
			break;
		case PF_Cmd_RENDER:
			error = Render (in_data, out_data, params, output);
			break;
		}
	} catch (PF_Err &thrown_error) {
		error = thrown_error;
	}

	return error;
}
