#include "SPIRV-Cross/spirv_msl.hpp"
#include "crossc-priv.h"

namespace {
	auto get_msl(crossc_compiler *comp)
	{
		return (spirv_cross::CompilerMSL*)comp->c.get();
	}
}

crossc_compiler *crossc_msl_create(const uint32_t *words, size_t word_count)
{
	crossc_compiler *comp = new crossc_compiler;
	try {
		comp->c = std::make_unique<spirv_cross::CompilerMSL>(words, word_count);
	} catch (const std::exception &e) {
		comp->error = std::string { e.what() };
	}
	return comp;
}

void crossc_msl_set_shader_version(crossc_compiler *comp, uint32_t major,
                                   uint32_t minor, uint32_t patch)
{
	if (!comp->c)
		return;
	auto msl = get_msl(comp);
	auto opts = msl->get_msl_options();
	opts.set_msl_version(major, minor, patch);
	msl->set_msl_options(opts);
}
