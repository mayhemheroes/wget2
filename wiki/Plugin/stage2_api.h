// API Exposed for plugins for intercepting URLs:

/// Stores any action taken by the plugin
typedef struct {
	wget_plugin_vtable *vtable;	
} wget_intercept_action_t;

/**
 * Marks the URL to be rejected. The URL will not be fetched by wget2 or passed to remaining plugins.
 *
 * Mutually exclusive with `wget_intercept_action_accept()`.
 * 
 * \param action Handle for any action taken by the plugin
 */
WGETAPI void
wget_intercept_action_reject(wget_intercept_action_t *action);

/**
 * Marks the URL to be accepted. The URL will not be passed to remaining plugins. wget2 will not filter the URL 
 * by any accept or reject pattern.
 *
 * Mutually exclusive with `wget_intercept_action_reject()`.
 * 
 * \param action Handle for any action taken by the plugin
 */
WGETAPI void
wget_intercept_action_accept(wget_intercept_action_t *action);

/**
 * Specifies an alternative URL to be fetched instead.
 * 
 * \param action Handle for any action taken by the plugin
 * \param iri Alternative URL to be fetched
 */
WGETAPI void
wget_intercept_action_set_alt_url(wget_intercept_action_t *action, const wget_iri_t *iri);

/**
 * Specifies that the fetched data should be written to an alternative file.
 * 
 * \param action Handle for any action taken by the plugin
 * \param local_filename Alternative file name to use
 */
WGETAPI void
wget_intercept_action_set_local_filename(wget_intercept_action_t *action, const char *local_filename);

/**
 * Prototype for the function for intercepting URLs
 * The function must be thread-safe.
 *
 * \param[in] plugin The plugin handle
 * \param[in] iri The URL about to be fetched
 * \param[in] action Output the action to be taken
 */
typedef void (*wget_plugin_url_filter_t)(wget_plugin_t *plugin, const wget_iri_t *iri, wget_intercept_action_t *action);

/**
 * Registers a plugin function for intercepting URLs
 *
 * \param[in] plugin The plugin handle
 * \param[in] filter_fn The plugin function that will be passed the URL to be fetched
 */
WGETAPI void
wget_plugin_register_url_filter(wget_plugin_t *plugin, wget_plugin_url_filter_t filter_fn);

// plugin vtable will be extended like
struct wget_plugin_vtable {
	...

	void (* action_reject)(wget_intercept_action_t *);
	void (* action_accept)(wget_intercept_action_t *);
	void (* action_set_alt_url)(wget_intercept_action_t *, const wget_iri_t *);
	void (* action_set_local_filename)(wget_intercept_action_t *, const char *);

	void (*register_url_filter)(wget_plugin_t *, wget_plugin_url_filter_t);
};
