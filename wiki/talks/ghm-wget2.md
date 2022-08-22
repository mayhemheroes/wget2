# [GHM] Wget2

This page is for getting a basic outline ready for GHM. Once ready, we can make a presentation. If we finish in time, it can be presented at GHM.

*EDIT:* The talk was ready and presented at GHM, 2017. [[PDF](http://audio-video.gnu.org/video/ghm2017/2017-08--ruhsen-shah--wget--ghm.pdf)]  [[Video](http://audio-video.gnu.org/video/ghm2017/2017-08--ruhsen-shah--wget--ghm.webm)]

# Outline

## What is Wget
Wget is a command line download tool for http(s) and ftp(s) resources.

It's specialty is the so-called "recursive" download of complete web pages, e.g. for local mirroring, for proxy preloading, analyzing, testing, ...

## Why Wget2 ?
To achieve a real parallel operation of Wget the existing code base needed a complete rewrite. Some points were old convoluted codebase, lack of unit tests, difficults to add new features, single threaded design (blocking sockets, static/global variables, non-reentrant code), C89.

It was clear that a rewrite would never be 100% compatible and the Wget maintainers weren't very happy. So the new project was named 'Mget' and was designed with multi-threading, C99 and POSIX in mind.

Multi-threaded download worked after a few days... but to implement all those gory details took a while...

## Wget2 - a short history

In 2013 reusable code was moved into a link library (libmget), something that allows external programs to use Mget functionality. Basically, Mget became a complex "example" code of how to use the libmget API.

In 2015, after adding HTTP/2 functionality, the Wget maintainers (meanwhile I became one of them) could be convinced to take Mget as a Wget successor. We called it Wget2 (and libwget) to allow easy parallel installation with Wget1.x and to support a smooth transition of scripts and programs.

In 2016 we concentrated on portability, pulled in gnulib, added Continuous Integration (CI) for different OSes (Linux, Solaris, OSX/BSD, MinGW64).

In 2017 we got 3 GSOC students to work on Wget2 project (plugin architecture, test suite based on libmicrohttpd, statistics module).

In 2017 we integrated fuzzing to cover the main parts of libwget.

During the development we also improved and created projects that Wget2 is dependent on.
This is libpsl to check cookie domains against the Mozilla Public Suffix List, which now is in all big Linux distros. We added TR46 support to libidn2 to make IDNA2008 support complete. We added TCP Fast Open support for GnuTLS (Linux and OSX) - the first TLS library with direct TFO support (AFAIK). We transfered our fuzzer knowledge to libidn2, libidn and libpsl - and found and fixed several bugs in all three projects.

??? First release

## Wget2 features
- Built around a LGPL Library, libwget (a la libcurl)
- Backwards compatible with common Wget switches
- Faster (CPU and real time, less disk access)
- More secure
- Multi-Threaded Downloading (even of single files, --chunk-size)
- recursive config files (include directive)
- HTTP/2 (and non-blocking sockets)
- HTTP Compression (gzip, bz2, xz, lxma, brotli)
- TCP Fast Open (HTTP *and* HTTPS)
- TLS False Start / TLS Session Resumption
- Metalink support (Version 3, RFC 5854 (.meta4), RFC 6249 (HTTP))
- IDNA 2008 + TR46 support
- XDG Compliant
- Cookie security with LibPSL (also in Wget 1.x, library forked from mget code)
- HSTS (also in Wget 1.x)
- HPKP (HTTP Public Key Pinning)
- `--secure-protocol=PFS`
- OCSP incl. caching
- Streaming support (ICEcast/SHOUTcast, see examples/getstream.c)
- Scans Atom 1.0, RSS 2.0, Sitemap files (XML, plain text)


## Future enhancements (examples)
- FTP / FTPS (maybe never makes it into Wget2, perhaps a wget2-ftp executable to separate protocols).
- Certificate Transparency (CT)
- Quic (is there a GPL'ed libquic ?)
- DASH (Dynamic Adaptive Streaming over HTTP) e.g. used by the BBC
- TLS 1.3 (ongoing work in GnuTLS with Ander Juaristi's help, standard not finalized yet)

## On-Going Work
- GSoC: Plugin Framework
- GSoC: Stats Framework
- GSoC: New tests suite using GNU libmicrohttpd

## Quality Assurance
- Continuous Integration using Gitlab CI and Travis CI
  - GNU/Linux, OSX, MinGW
  - gcc and clang
  - Sanitizers (undefined and address)
- Continuous Fuzzing for libwget (using OSS-Fuzz)
- Unit testing for libwget API
- Regression testing for libwget API (using fuzzing test corpora)
- Functionality testing for Wget2 incl. HTTP test server
- Regular Coverity scans
- Tests also written in C for easy maintainability (no Perl, Python, Ruby or whatever experts needed)

## Path to Initial Public Release
- Need more testers / contributors
- Some more options have to be implemented
- Proxy tunneling (HTTPS proxy)
- Finalization of APIs
- Documentation
- Fixing bugs