// API Exposed for plugins for custom HSTS, HPKP and OCSP databases

/**
 * Provides wget2 with another HSTS database to use.
 *
 * Each database, including wget2's own implementation, has an integer value known as priority associated with it. 
 * The implementation with the highest priority value is actually used by wget2. 
 *
 * wget2's own implementation has priority value 0.
 *
 * wget2 will automatically call wget_hsts_db_free() on any database it decides it no longer needs,
 * so plugins do not need to do so.
 *
 * \param[in] plugin The plugin handle
 * \param[in] hsts_db HSTS database to add
 * \param[in] priority The priority value to use
 */
WGETAPI void wget_plugin_add_hsts_db(wget_plugin_t *plugin, wget_hsts_db_t *hsts_db, int priority);

/**
 * Provides wget2 with another HPKP database to use.
 *
 * Each database, including wget2's own implementation, has an integer value known as priority associated with it. 
 * The implementation with the highest priority value is actually used by wget2. 
 *
 * wget2's own implementation has priority value 0.
 *
 * wget2 will automatically call wget_hpkp_db_free() on any database it decides it no longer needs,
 * so plugins do not need to do so.
 *
 * \param[in] plugin The plugin handle
 * \param[in] hpkp_db HPKP database to add
 * \param[in] priority The priority value to use
 */
WGETAPI void wget_plugin_add_hpkp_db(wget_plugin_t *plugin, wget_hpkp_db_t *hpkp_db, int priority);

/**
 * Provides wget2 with another OCSP database to use.
 *
 * Each database, including wget2's own implementation, has an integer value known as priority associated with it. 
 * The implementation with the highest priority value is actually used by wget2. 
 *
 * wget2's own implementation has priority value 0.
 *
 * wget2 will automatically call wget_ocsp_db_free() on any database it decides it no longer needs,
 * so plugins do not need to do so.
 *
 * \param[in] plugin The plugin handle
 * \param[in] ocsp_db OCSP database to add
 * \param[in] priority The priority value to use
 */
WGETAPI void wget_plugin_add_ocsp_db(wget_plugin_t *plugin, wget_ocsp_db_t *ocsp_db, int priority);

// plugin vtable will be extended like
struct wget_plugin_vtable {
	...
	void (*add_hsts_db)(wget_plugin_t *, wget_hsts_db_t *, int);
	void (*add_hpkp_db)(wget_plugin_t *, wget_hpkp_db_t *, int);
	void (*add_ocsp_db)(wget_plugin_t *, wget_ocsp_db_t *, int);
};

