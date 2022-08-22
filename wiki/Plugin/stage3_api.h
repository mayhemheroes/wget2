// API Exposed for plugins for intercepting downloaded files:

/// Handle that represents a downloaded file.
typedef struct {
	struct wget_plugin_vtable *vtable;
} wget_downloaded_file_t;

/**
 * Gets the source address the file was downloaded from.
 *
 * \param[in] file Downloaded file handle
 * \return The address the file was downloaded from. The returned object is owned by wget and should not be free'd.
 */
const wget_iri_t *wget_downloaded_file_get_source_url(wget_downloaded_file_t *file);

/**
 * Gets the file name the downloaded file was written to.
 *
 * \param[in] file Downloaded file handle
 * \return The file name the file was written to. The returned string is owned by wget and should not be free'd.
 */
const char *wget_downloaded_file_get_local_filename(wget_downloaded_file_t *file);

/**
 * Gets the size of the downloaded file.
 *
 * \param[in] file Downloaded file handle
 * \return The size of the downloaded file
 */
uint64_t wget_downloaded_file_get_size(wget_downloaded_file_t *file);

/**
 * Reads the downloaded file into memory.
 *
 * Be careful, reading large files into memory can cause all sorts of problems like running out of memory.
 * Use \ref wget_downloaded_file_open_stream "wget_downloaded_file_open_stream()" whenever possible.
 *
 * \param[in] file Downloaded file handle
 * \param[out] data The contents of the downloaded file.
 *                  The memory is owned by wget and must not be free'd or modified.
 * \param[out] size Size of the downloaded file.
 * \return 0 if the operation was successful, -1 in case of any failures 
 *           (out parameters are not modified in case of failure)
 */
int wget_downloaded_file_get_contents(wget_downloaded_file_t *file, const void **data, size_t *size);

/**
 * Opens the downloaded file as a new stream.
 *
 * \param[in] file Downloaded file handle
 * \return A newly opened stream, or NULL in case of any failures.
 *         The returned stream must be closed with fclose() after use.
 */
FILE *wget_downloaded_file_open_stream(wget_downloaded_file_t *file);

/**
 * Gets whether the file should be scanned for more URLs.
 *
 * \param[in] file Downloaded file handle
 * \return whether the file should be scanned for more URLs.
 */
bool wget_downloaded_file_get_recurse(wget_downloaded_file_t *file);

/**
 * Adds a URL for recursive downloading.
 * This function has no effect if `wget_downloaded_file_get_recurse` returns false.
 *
 * \param[in] file Downloaded file handle
 * \param[in] iri The URL to be fetched.
 */
void wget_downloaded_file_add_recurse_url(wget_downloaded_file_t *file, const wget_iri_t *iri);

/**
 * Prototype of the function for intercepting downloaded files. The function must be thread-safe.
 *
 * \param[in] plugin The plugin handle
 * \param[in] file Downloaded file handle
 * \return 0 if further postprocessing of downloaded files should be stopped.
 */
typedef int (*wget_plugin_post_processor_t)
	(wget_plugin_t *plugin, wget_downloaded_file_t *file);

/**
 * Registers a plugin function for intercepting downloaded files.
 *
 * \param[in] plugin The plugin handle
 * \param[in] fn The plugin function that will be passed a handle to downloaded files.
 */
WGETAPI void
wget_plugin_register_post_processor(wget_plugin_t *plugin, wget_plugin_post_processor_t fn);

// plugin vtable will be extended like
struct wget_plugin_vtable {
	...
	void (*register_post_processor)(wget_plugin_t *, wget_plugin_post_processor_t);

	const wget_iri_t *(*file_get_source_url)(wget_downloaded_file_t *);
	const char *(*file_get_local_filename)(wget_downloaded_file_t *);
	uint64_t (*file_get_size)(wget_downloaded_file_t *);
	void (*file_get_contents)(wget_downloaded_file_t *, const void **data, size_t *size);
	FILE *(*file_open_stream)(wget_downloaded_file_t *);
	bool (*file_get_recurse)(wget_downloaded_file_t *);
	void (*file_add_recurse_url)(wget_downloaded_file_t *, const wget_iri_t *);
};

