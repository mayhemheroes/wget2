# API for intercepting downloaded files

## Specifications
- Plugin registered functions shall be called whenever wget2 fetches a file successfully.
- On receiving file contents, registered plugin function can then send back
  a list of URLs to fetch if the download was recursive

## Implementation details
- `process_response()` in `src/wget.c` shall be modified to call functions in `src/plugin.c` which will in turn 
  calls all the registered plugin functions.
- Only a file handle is passed which allows plugins to access file contents in the way they prefer. This will also
  allow for easier future expansion of the API.

## Interface for the plugin
- See [stage3_api.h](stage3_api.h)

## Links
- Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/248
- Commit : https://gitlab.com/gnuwget/wget2/commit/81cada6b7ddd497bd56dfa33e0b03dc095457d0f
