#include <obs-module.h>
#include "plugin-macros.generated.h"

static const char *get_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);
	return obs_module_text("Mute.Name");
}

static void *create(obs_data_t *settings, obs_source_t *source)
{
	UNUSED_PARAMETER(settings);

	return source;
}

static void destroy(void *data)
{
	UNUSED_PARAMETER(data);
}

static struct obs_audio_data *mute_filter_audio(void *data, struct obs_audio_data *audio)
{
	UNUSED_PARAMETER(data);
	UNUSED_PARAMETER(audio);

	return NULL;
}

const struct obs_source_info mute_filter_info = {
	.id = ID_PREFIX "mute-filter",
	.type = OBS_SOURCE_TYPE_FILTER,
	.output_flags = OBS_SOURCE_AUDIO,
	.get_name = get_name,
	.create = create,
	.destroy = destroy,
	.filter_audio = mute_filter_audio,
};
