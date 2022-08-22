# Stage 0: Plugin loading mechanism

## Terminology
 - Plugin: An module that affects the functioning of wget2 in any way.
   A plugin is supposed to be initialized by its initializer function.
   When wget exits normally, plugin's finalizer function is called. 
 - Object file: .so or .dll file from where a plugin may be dynamically loaded
 - Initializer function: A function in a plugin which shall be called to 
   initialize the plugin. Initializer function is supposed to use the plugin 
   API to affect wget in any way and possibly register a finalizer function.
 - Finalizer function: A function in a plugin which shall be called when wget2
   exits normally. This function is optional.

## Plugin load method
 - Description of the plugin is received. Description could be:
    - Name of the plugin. The name does not have any leading path component
	  or `lib` prefix or trailing `.so` or `.dll`.
    - Path of the object file.
 - Open the object file. Only needed if initializer function is 
   not already known. If path to the object file is not known, 
   wget2 shall construct filename by adding platform-specific
   prefix and suffix and search for the filename in the plugin search paths
   to find the object file.
 - Load `wget_plugin_initializer` symbol. Only needed if initializer function 
   is not already known.
 - Call the initializer function.

## Plugin search path
 - It is one of the directories where wget2 will search for object files 
   corresponding to the plugin to load.
 - By default wget2 will use only one directory `$(prefix)/lib/wget2/plugins`.
   More directories may be added by command line options (and wgetrc)
   and environment variable.

## Interface for the user
 - Option `--plugin=foo`: Loads plugin `foo` by searching for them in plugin
   search paths. 
   `--plugin=` may be specified multiple times, like 
   `--plugin=foo --plugin=bar` will load both `foo` and `bar`.
 - Environment variable `WGET2_PLUGINS=foo`: Loads plugin `foo` like above.
   Multiple plugins may be separated by a colon like `WGET2_PLUGINS=foo:bar`
 - Option `--local-plugin=/path/to/libfoo.so` or 
   `--local-plugin=/path/to/foo.dll`: Loads plugin `foo` 
 - Option `--plugin-dirs=list`: Specifies alternative plugin search paths 
   instead of `$(prefix)/lib/wget2/plugins`.
 - Environment variable `WGET2_PLUGIN_DIRS=list`: 
   Specifies alternative plugin search paths instead of 
   `$(prefix)/lib/wget2/plugins`.
 - Option `--list-plugins`: Lists all plugins found in plugin search paths.

## Implementation details
 - Module _dl_ (`src/dl.c`, `src/wget_dl.h`) will be added that will contain
   an abstraction to load object files. `unit-tests/test-dl.c` will be added
   for testing.
 - Module _plugin_ (`src/plugin.c`, `src/wget_plugin.h`) will be added
   which will implement wget plugin loading using `src/wget_dl.h`
 - The plugin API will be added in `libwget/plugin.c`. Functions defined
   there will often use a vtable, with actual implementation done in 
   `src/plugin.c`.
 - `src/options.c` and `src/wget.c` will be adjusted accordingly to call 
   relevant functions from `wget_plugin.h`.

## Proposed plugin API
See [stage0_api.h](stage0_api.h) for the functions exposed for plugins 
in `include/wget/wget.h`.

## Links
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/222
 - Commit: https://gitlab.com/gnuwget/wget2/commit/4d3b3f5167a022d099e162553ee93a324331bc84
