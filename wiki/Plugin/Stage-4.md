# API for custom HSTS, HPKP and OCSP databases

## Specifications
- wget_hsts_db_t, wget_hpkp_db_t and wget_ocsp_db_t 
  shall be made an abstract class. (Some functions need to be changed)
- The current implementations for 
  wget_hsts_db_t, wget_hpkp_db_t and wget_ocsp_db_t shall be retained as a
  'derrived class'.
- Plugins are able to extend the abstract classes type and provide their own
  implementation using a vtable.
- wget2 shall select database implementation by plugin-provided priority.
  Implementation with highest priority shall be used. wget2's own 
  implementation shall have priority 0.
  
## wget_hsts_db_t abstract class design
- See [stage4_hsts.h](stage4_hsts.h)

## wget_hpkp_db_t abstract class design
- See [stage4_hpkp.h](stage4_hpkp.h)

## wget_ocsp_db_t abstract class design
- See [stage4_ocsp.h](stage4_ocsp.h)

## Interface for the plugin
- See [stage4_api.h](stage4_api.h)

## Links
- Merge request: https://gitlab.com/gnuwget/wget2/merge_requests/262
- Commit : https://gitlab.com/gnuwget/wget2/commit/98c8e410a84b9178bf6a8b8b97f3204a8a87b939
