# Wget2 plugin support implementation

## Introduction

This wiki documents my GSoc 2017 project entitled 
'Design and implementation of framework for plugins'.

wget2 is a CLI HTTP client. This project added to wget2 ability to load plugins
which then could influence its behavior.

Plugin support implementation was done in stages.


## Stage 0: Plugin loading mechanism

This stage implemented loading plugins. Windows and platforms using libdl 
are supported. No useful plugin API was added in this stage.

`--plugin` command line option was added for loading an installed plugin.
User is also able to load plugins from arbitrary locations by `--local-plugin`
option.

__Modules added__
- `libwget/plugin.c`: Plugin API.
- `src/plugin.c`: Plugin management and API implementation.
- `src/dl.c`: Abstraction for dynamic loading of object files.

wget2 plugins are shared libraries having `wget_plugin_initializer()` function
and linked agains libwget. wget2 calls `wget_plugin_initializer()` on loading
a plugin and expects the function to register all the hooks the plugin is 
interested in.

__Links__
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/222
 - Commit: https://gitlab.com/gnuwget/wget2/commit/4d3b3f5167a022d099e162553ee93a324331bc84

## Stage 1: Command line option forwarding

This stage implemented forwarding command line options to plugins.
Any option in form of `--plugin-option=<plugin_name>.<option>[=<value>]` is 
forwarded to plugin `<plugin_name>`. 

__Links__
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/233
 - Commit:https://gitlab.com/gnuwget/wget2/commit/c3a0e8ac4781ba81b7693f0424bc3ccf7a60dd2b 

## Stage 2: API for intercepting URLs

This stage enabled plugins to intercept URLs added to the download queue.

Plugins are able to reject URLs from being downloaded, and change
URLs and downloaded file name before adding to the queue.

__Links__
 - Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/243
 - Commit: https://gitlab.com/gnuwget/wget2/commit/892e4ac761923e2aefd01666d723f71a722f8909

## Stage 3: API for intercepting downloaded files

This stage enabled plugins to intercept downloaded files. 

Plugins are able to read downloaded files, and optionally scan files for
additional URLs and push them into the download queue.

__Links:__
- Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/248
- Commit : https://gitlab.com/gnuwget/wget2/commit/81cada6b7ddd497bd56dfa33e0b03dc095457d0f

## Stage 4: API for implementing custom HSTS, HPKP and OCSP databases.

This stage enabled plugins to custom databases for HSTS, HPKP, and OCSP. 

For implementing
[HSTS](https://en.wikipedia.org/wiki/HTTP_Strict_Transport_Security), 
[HPKP](https://en.wikipedia.org/wiki/HTTP_Public_Key_Pinning) and
[OCSP](https://en.wikipedia.org/wiki/Online_Certificate_Status_Protocol),
wget2 needs to store persistent data between runs. 
This is stored in flat files `.wget-hsts`, `.wget-hpkp` and `.wget-ocsp`
respectively. This stage allows the persistent data to be loaded from arbitrary
sources and allows plugins to supply their own databases. 

__Links:__
- Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/262
- Commit : https://gitlab.com/gnuwget/wget2/commit/98c8e410a84b9178bf6a8b8b97f3204a8a87b939

## Testing

- Unit test `unit-tests/test-dl.c` was added for testing `src/dl.c` abstraction.
- `tests/test-plugin.c` was added for testing all plugin-related functionality.

__Coverage__ (https://coveralls.io/github/akashrawal/wget2?branch=gsoc17_snapshot)

| File                | Line coverage | function coverage |
|---------------------|---------------|-------------------|
| `libwget/plugin.c`  | 100%          | 100%              |
| `src/dl.c`          | 92.7%         | 100%              |
| `src/plugin.c`      | 96.6%         | 100%              |


## What I learnt

- __Writing tests that execute in a finite time.__
  So far the tests I write were like, write test code to generate random input,
  execute the code in question, and write an acceptor function to check for
  correctness. Then run the test program under valgrind and wait patiently
  for assertion failures or memory errors. 
  Working under wget2 taught me to write tests that cover almost all possible
  cases guided by `lcov` coverage reports.
- __Developing for windows.__
  My original plan was to offload testing on windows to others, but 
  during community bonding period I decided to give it a shot and attempted to 
  cross-compile wget2 for mingw64 and run the tests in `wine`. I discovered a 
  row of issues, fixing them essentially taught me to navigate through MSDN 
  and find out differences in behavior of library functions in windows.
  Using the experience I can now port some of my own projects to work on
  windows.


## Work mentioned in proposal but not done

- Ability for plugins to read, add and modify HTTP request and response headers
