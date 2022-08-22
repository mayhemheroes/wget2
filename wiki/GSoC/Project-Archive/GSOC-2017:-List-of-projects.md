Please also take a look [here](https://github.com/darnir/wget/wiki/Google-Summer-of-Code) for more information on how GNU Wget conducts GSoC, some FAQs and a sample proposal.

## Design and implementation of a test suite using libmicrohttpd.

The current test suite is written in C.
It uses home-grown HTTP(S) server code with all it's pros and cons.

Switching to a GNU licensed server code has several advantages:
- less maintenance for server code
- no need to write own server code for e.g. HTTP/2, HPKP, OCSP, Authentication, ...
- proper separation of projects
- code need for Wget2 testing also improves libmicrohttpd and more projects will benefit from that

Please also see issue https://github.com/rockdaboot/wget2/issues/128

**Skills:** C, HTTP (Server & Client), Multi-threading

**Difficulty:** Medium

**Possible mentors:** Christian Grothoff, Darshit Shah, Giuseppe Scrivano, Tim Rühsen


***
## Design and implementation of a framework for plugins

Plugins (*.so files on *nix) may be used to customize Wget's operation.

Examples:
- Post-scan: decide if scanned URLs should be downloaded or not
- Post-scan: modify scanned URLs before putting into download queue
- Post-download: decide if a downloaded file should be scanned or not
- Post-download: decide if a downloaded file should be saved or not
- Post-download: process a downloaded file (adding URLs to the download queue)
- Post-download: writing statistics
- Pre-download: Add custom headers, modify existing headers

References
https://savannah.gnu.org/bugs/index.php?45803
https://github.com/rockdaboot/wget2/issues/80

**Skills:** C, API Design, Multi-threading

**Difficulty:** Medium

**Possible mentors:** Darshit Shah, Giuseppe Scrivano, Tim Rühsen

***
## Design and implementation of a fuzzing framework for Wget2 and libwget

Wget2 relies heavily on libwget. The library functions have to be tested with all kinds of input. That's were a fuzzer enters the game. There are several fuzzers out there. But using libFuzzer (http://llvm.org/docs/LibFuzzer.html) has the advantage that we can possibly use the results at Google's OSS-Fuzz project (https://github.com/google/oss-fuzz).

Wget2 also has to be fuzzed of course.

**Skills:** C, Fuzzing

**Difficulty:** Easy

**Possible mentors:** Darshit Shah, Giuseppe Scrivano, Tim Rühsen


***
## Design and implementation of a statistics module

Different kinds of statistics may be of interest.
- Host-based:
  - duration of DNS lookups
  - plain text or TLS
  - version of TLS negotiation
  - duration of negotiation
  - size of cert chain (number of certificates)
  - support for TCP FastOpen, TLS session resumption, TLS false start, ...
  - OCSP lookup (not supported, no answer, positive answer, negative answer)
  - features of server (HSTS, HPKP, CSP, ...)
  - ...
  This could be done as stand-alone tool (e.g. for examples/)

- Site-based (--recursive):
  - number of documents by status
  - explicit list of documents by status
  - server response time per document (request until header)
  - size of documents / directory
  - references / relationship between document (maybe a tree'ish output as well)
  - ...


**Skills:** C

**Difficulty:** Easy

**Possible mentors:** Darshit Shah, Giuseppe Scrivano, Tim Rühsen
