# API for intercepting URLs

## Specifications
- Each URL shall be passed to all the registered plugin functions 
  in the order the plugins were loaded.
- On intercepting URLs, plugins can choose to do zero or more of the following:
  - Reject the URL. All further processing of the URL shall be aborted.
    Mutually exclusive with the 'accept' action. (see below)
  - Accepts the URL. (TODO: better terminology)
    All further processing shall be aborted and wget2 shall do no further 
    filtering like accept and reject patterns and enqueue the URL immediately.
	Mutually exclusive with the 'reject' option. (see above)
  - Suggest alternative URL. Plugin suggests some other URL should be 
    fetched instead. wget2 shall proceed with the new URL supplied by the plugin.
  - Suggest alternative output file name. wget2 shall write the output in 
    the suggested file name instead of the one given by `get_local_filename()`. 
	This action has no effect if `--output-document=` option is supplied.

## Implementation details
- `add_url_to_queue()` and `add_url()` at `src/wget.c` will be modified
  to call a function from `src/plugin.c` for each new URL,
  which will in turn allow plugins to intercept the new URLs.

## Interface for the plugin
- See [stage2_api.h](stage2_api.h)

## Links
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/243
 - Commit: https://gitlab.com/gnuwget/wget2/commit/892e4ac761923e2aefd01666d723f71a722f8909

