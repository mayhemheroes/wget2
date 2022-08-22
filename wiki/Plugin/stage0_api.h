//Forward declaration for the vtable
struct wget_plugin_vtable;

///Abstract handle used to identify the plugin.
typedef struct 
{
	///Plugin specific data. Plugins are free to assign any value to this.
	void *plugin_data;

	///Pointer to the vtable. Used by wget to implement functions.
	struct wget_plugin_vtable *vtable;	
} wget_plugin_t;


/**Prototype for the initializer function
* \param plugin Used to identify the plugin
* \return Should return 0 if initialization succeded, 
*         or any other value to indicate failure. 
*         On failure, wget2 will continue without the plugin
*         and will not call the finalizer function even if registered.
*/
typedef int 
(*wget_plugin_initializer_t)(wget_plugin_t *plugin);

/**Prototype of the finalizer function
* \param plugin Used to identify the plugin
* \param exit_status The exit status wget will exit with
*/
typedef void
(*wget_plugin_finalizer_t)(wget_plugin_t *plugin, int exit_status);

/**Registers a function to be called when wget exits.
* \param plugin Used to identify the plugin
* \param fn A function pointer to be called
*/
void 
wget_plugin_register_finalizer
		(wget_plugin_t *plugin, wget_plugin_finalizer_t fn);

///vtable for implementing plugin API in wget
struct wget_plugin_vtable
{
	void (* register_finalizer)(wget_plugin_t *, wget_plugin_finalizer_t);
};
