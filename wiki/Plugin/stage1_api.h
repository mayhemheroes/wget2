/**Prototype for the function that will accept forwarded command line arguments.
 * \param plugin Handle that identifies the plugin.
 * \param option Option name. If the option is "help", a help message must be
 *               printed to stdout.
 * \param value  The value of the option if provided, or NULL
 * \return Must return 0 if option and its value is valid, or any other value
 *         if invalid. In that case wget will exit.
 */
typedef int (*wget_argp_fn)
	(wget_plugin_t *plugin, const char *option, const char *value);

/**Registers a function for argument forwarding. 
 * \param plugin Handle that identifies the plugin.
 * \param fn The function pointer to register
 */
void wget_plugin_register_argp(wget_plugin_t *plugin, wget_argp_fn fn);

//plugin vtable will be extended like
struct wget_plugin_vtable
{
	...
	void (*register_argp)(wget_plugin_t *, wget_argp_fn);
};
