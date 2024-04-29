#include <obs-module.h>
#include "plugin-macros.generated.h"

#define TS_SMOOTHING_THRESHOLD 70000000ULL

struct mute_by_ui_s
{
	obs_source_t *ctx;

	obs_weak_source_t *weak_parent;
	bool configured;
	volatile bool parent_muted;
	bool last_muted;
	uint64_t last_audio_ns;
};

static const char *get_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);
	return obs_module_text("MuteByUI.Name");
}

static void *create(obs_data_t *settings, obs_source_t *source)
{
	UNUSED_PARAMETER(settings);

	struct mute_by_ui_s *m = bzalloc(sizeof(struct mute_by_ui_s));
	m->ctx = source;

	return m;
}

static void mute_cb(void *data, calldata_t *cd)
{
	struct mute_by_ui_s *m = data;
	m->parent_muted = calldata_bool(cd, "muted");
}

static void configure_callback(struct mute_by_ui_s *m)
{
	obs_source_t *parent = obs_filter_get_parent(m->ctx);
	if (!parent)
		return;

	signal_handler_t *sh = obs_source_get_signal_handler(parent);
	signal_handler_connect(sh, "mute", mute_cb, m);

	m->parent_muted = obs_source_muted(parent);
	m->weak_parent = obs_source_get_weak_source(parent);

	m->configured = true;
}

static void destroy(void *data)
{
	struct mute_by_ui_s *m = data;

	if (m->configured) {
		obs_source_t *parent = obs_weak_source_get_source(m->weak_parent);
		signal_handler_t *sh = obs_source_get_signal_handler(parent);
		signal_handler_disconnect(sh, "mute", mute_cb, m);
		obs_source_release(parent);
		obs_weak_source_release(m->weak_parent);
	}

	bfree(m);
}

static struct obs_audio_data *mute_filter_audio(void *data, struct obs_audio_data *audio)
{
	struct mute_by_ui_s *m = data;

	if (!m->configured)
		configure_callback(m);

	if (m->parent_muted) {
		m->last_muted = true;
		return NULL;
	}

	if (m->last_muted && audio->timestamp - m->last_audio_ns < TS_SMOOTHING_THRESHOLD) {
		return NULL;
	}

	m->last_muted = false;
	m->last_audio_ns = audio->timestamp;
	return audio;
}

const struct obs_source_info mute_filter_by_ui_info = {
	.id = ID_PREFIX "mute-filter-by-ui",
	.type = OBS_SOURCE_TYPE_FILTER,
	.output_flags = OBS_SOURCE_AUDIO,
	.get_name = get_name,
	.create = create,
	.destroy = destroy,
	.filter_audio = mute_filter_audio,
};
