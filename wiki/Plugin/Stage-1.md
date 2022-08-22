# Command line argument forwarding

## Argument forwarding method
 - Only arguments that are not accepted by wget may be forwarded.
 - Argument for forwarding must be in the form 
   `--plugin-opt=<plugin-name>.<option>[=<value>]`.
 - `--plugin-opt=` option shall be implemented that shall call a function
   in `src/plugin.c`.
 - The function shall parse the plugin option, separate plugin name,
   option, and value and pass it to the plugin, or report appropriate error.

## Interface for the user
 - Option `--plugin-opt=<plugin-name>.<option>[=<value>]`: 
   Sends `<option>=<value>` to plugin `<plugin>`. 
   '.' is considered as delimiter and the string before
   the first '.' will be taken as plugin name.
 - Option `--plugin-help`: Prints help message for each plugin loaded.
 - Plugin must be loaded before plugin-specific option is specified. 
   e.g. `--plugin=foo --plugin-foo-option` is valid but 
   `--plugin-foo-option --plugin=foo` will cause an error. 

## Interface for the plugin
 - See [stage1_api.h](stage1_api.h).

## Links
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/233
 - Commit:https://gitlab.com/gnuwget/wget2/commit/c3a0e8ac4781ba81b7693f0424bc3ccf7a60dd2b 
