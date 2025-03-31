#include "./nothing.hh"


//* About *//

static PF_Err About (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	in_data->utils->ansi.sprintf (
		out_data->return_msg,
		"%s v%d.%d\r%s\r%s",
		"Nothing",
		MAJOR_VERSION,
		MINOR_VERSION,
		"This plugin adds even more amazing visual effects to your sophisticated workflow.",
		"Experience this incredible power XD"
	);

	return error;
}


//* Global Setup *//

static PF_Err GlobalSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	out_data->my_version = PF_VERSION (
		MAJOR_VERSION,
		MINOR_VERSION,
		BUG_VERSION,
		STAGE_VERSION,
		BUILD_VERSION
	);

	out_data->out_flags = PF_OutFlag_DEEP_COLOR_AWARE | PF_OutFlag_PIX_INDEPENDENT;
	out_data->out_flags2 = PF_OutFlag2_SUPPORTS_THREADED_RENDERING | PF_OutFlag2_SUPPORTS_SMART_RENDER | PF_OutFlag2_FLOAT_COLOR_AWARE;

	return error;
}


//* Params Setup *//

static PF_Err ParamsSetup (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	out_data->num_params = 1;  // only layer

	return error;
}


//* Render *//

static PF_Err Render (PF_InData *in_data, PF_OutData *out_data, PF_ParamDef *params[], PF_LayerDef *output) {
	PF_Err error = PF_Err_NONE;

	error = in_data->utils->copy (
		in_data->effect_ref,
		&params[0]->u.ld,
		output,
		NULL,
		NULL
	);

	return error;
}


//* Smart Pre Render *//

static PF_Err SmartPreRender (PF_InData *in_data, PF_OutData *out_data, PF_PreRenderExtra *extra) {
	PF_Err error = PF_Err_NONE;


	PF_RenderRequest request = extra->input->output_request;
	PF_CheckoutResult in_result;

	request.channel_mask = PF_ChannelMask_ARGB;
	request.preserve_rgb_of_zero_alpha = true;


	error = extra->cb->checkout_layer (
		in_data->effect_ref,
		0,
		0,
		&request,
		in_data->current_time,
		in_data->time_step,
		in_data->time_scale,
		&in_result
	);

	UnionLRect (&in_result.result_rect, &extra->output->result_rect);
	UnionLRect (&in_result.max_result_rect, &extra->output->max_result_rect);


	return error;
}


//* Smart Render *//

static PF_Err SmartRender (PF_InData *in_data, PF_OutData *out_data, PF_SmartRenderExtra *extra) {
	PF_Err error, error2 = PF_Err_NONE;


	PF_EffectWorld *input_world;
	PF_EffectWorld *output_world;

	AEGP_SuiteHandler suites (in_data->pica_basicP);


	error = extra->cb->checkout_layer_pixels (in_data->effect_ref, 0, &input_world);
	error = extra->cb->checkout_output (in_data->effect_ref, &output_world);


	if (!error) {
		error = suites.WorldTransformSuite1()->copy_hq (
			in_data->effect_ref,
			input_world,
			output_world,
			NULL,
			NULL
		);
	}


	error2 = extra->cb->checkin_layer_pixels (in_data->effect_ref, 0);

	return error;
}


//* Resources *//

extern "C" {
	DllExport PF_Err PluginDataEntryFunction2 (PF_PluginDataPtr inPtr, PF_PluginDataCB2 inPluginDataCallBackPtr, SPBasicSuite *inSPBasicSuitePtr, const char *inHostName, const char *inHostVersion) {
		PF_Err result = PF_Err_INVALID_CALLBACK;

		result = PF_REGISTER_EFFECT_EXT2 (
			inPtr,
			inPluginDataCallBackPtr,
			"Nothing",
			"POTI NOTHING",
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

			case PF_Cmd_SMART_PRE_RENDER:
			error = SmartPreRender (in_data, out_data, (PF_PreRenderExtra *)extra);
			break;

		case PF_Cmd_SMART_RENDER:
			error = SmartRender (in_data, out_data, (PF_SmartRenderExtra *)extra);
			break;
		}
	} catch (PF_Err &thrown_error) {
		error = thrown_error;
	}

	return error;
}
