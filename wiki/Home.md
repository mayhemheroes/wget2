# Wget2 Introduction

The development of Wget2 started and everybody is invited to contribute, test,
discuss, etc.<br>
The codebase is hosted in the 'wget2' branch of wget's git repository, on
Gitlab and on Github - all will be regularly synced.

  [Wget2 on Savannah](https://savannah.gnu.org/git/?group=wget) (currently just has wget infos)

  [Wget2 on Gitlab](https://gitlab.com/rockdaboot/wget2)

  [Wget2 on Github](https://github.com/rockdaboot/wget2)

The idea is to have a fresh and maintainable codebase with features like
multithreaded downloads, HTTP2, OCSP, HSTS, Metalink, IDNA2008, Public Suffix
List, Multi-Proxies, Sitemaps, Atom/RSS Feeds, compression (gzip, deflate,
lzma, bzip2), support for local filenames, etc.<br>
Some of these feature have been built into Wget in the meantime, but some
other are really hard to implement into the old codebase.

Most of the functionality is exposed via library API (libwget), to allow
external programs make use of it. E.g. have a look at
`examples/print_css_urls.c` - just a few lines of C to parse and print out all
URLs from a CSS file.

Wget2 will stay as an own executable separate from Wget.<br>
So you can install and test Wget2 without endangering your existing architecture and
scripts.

## What is missing

- FTP(S) support
- WARC support
- Several Wget options are missing.
- API documentation incomplete

## New options

    --check-hostname    Check the server's certificate's hostname. (default: on)
    --chunk-size        Download large files in multithreaded chunks. (default: 0 (=off))
                        Example: wget --chunk-size=1M
    --cookie-suffixes   Load public suffixes from file. They prevent 'supercookie' vulnerabilities.
    --cut-file-get-vars Cut HTTP GET vars from file names. (default: off)
    --cut-url-get-vars  Cut HTTP GET vars from URLs. (default: off)
    --dns-cache-preload File to be used to preload the DNS cache.
    --force-atom        Treat input file as Atom Feed. (default: off)
    --force-css         Treat input file as CSS. (default: off)
    --force-metalink    Treat input file as Metalink. (default: off)
    --force-rss         Treat input file as RSS Feed. (default: off)
    --force-sitemap     Treat input file as Sitemap. (default: off)
    --fsync-policy      Use fsync() to wait for data being written to the pysical layer. (default: off)
    --max-threads       Max. concurrent download threads. (default: 5)
    --metalink          Parse and follow metalink files and don't save them (default: on)
    --ocsp              Use OCSP server access to verify server's certificate. (default: on)
    --ocsp-file         Set file for OCSP chaching. (default: .wget_ocsp)
    --ocsp-date         Check if OCSP response is too old. (default: on)
    --ocsp-nonce        Allow nonce checking when verifying OCSP response. (default: on)
    --ocsp-server       Set OCSP server address (default: OCSP server given in certificate).
    --ocsp-stapling     Use OCSP stapling to verify the server's certificate. (default: on)
    --hsts              Use HTTP Strict Transport Security (HSTS). (default: on)
    --hsts-file         Set file for HSTS caching. (default: ~/.wget-hsts)
    --hsts-preload      Preload HTTP Strict Transport Security (HSTS) data via libhsts.
    --hsts-preload-file Set name for the HSTS Preload file (DAFSA format).
    --http2             Use HTTP/2 protocol if possible. (default: on)
    --http2-request-window  Max. number of parallel streams per HTTP/2 connection. (default: 30)
    --http-proxy        Set HTTP proxy/proxies, overriding environment variables.
    --https-enforce     Use secure HTTPS instead of HTTP.
    --https-proxy       Set HTTPS proxy/proxies, overriding environment variables.
    --input-encoding    Character encoding of the file contents read with --input-file. (default: local encoding)
    --random-file       File to be used as source of random data.
    --retry-on-http-status  Specify a list of http statuses in which the download will be retried.
    --robots            Respect robots.txt standard for recursive downloads. (default: on)
    --save-content-on   Specify a list of response codes that requires it's response body to be saved on error status
    --stats-all         Print all stats (default: off)
    --stats-dns         Print DNS stats. (default: off)
    --stats-ocsp        Print OCSP stats. (default: off)
    --stats-server      Print server stats. (default: off)
    --stats-site        Print site stats. (default: off)
    --stats-tls         Print TLS stats. (default: off)
    --tcp-fastopen      Enable TCP Fast Open (TFO). (default: on)
    --tls-false-start   Enable TLS False Start (needs GnuTLS 3.5+). (default: on)
    --tls-resume        Enable TLS Session Resumption. (default: on)
    --tls-session-file  Set file for TLS Session caching. (default: ~/.wget-session)

## Different behavior of Wget2
- new 'include' statement for config files, e.g. to load /etc/wget/conf.d/*.conf
- --input-file - (reading URLs from stdin) starts downloading with the first
  URL to allow slow URL generators feed Wget2
- check HTTP 'ETag' to avoid parsing doublettes
- use HTTP 'Accept-Encoding': gzip, deflate, lzma, bzip2, br
- CLI string options can be set to NULL by prepending a --no-, e.g. --no-user-agent
- boolean CLI options can all be set to true or false
- $WGETRC is not read so far

## Differing CLI options Wget/Wget2

Option|Wget|Wget2|Comment
------|----|-----|-------
--check-hostname||✓|
--chunk-size||✓|
--config|✓|✓|Same as --config-file, for compatibilty with Wget1.x
--config-file||✓|
--cookie-suffixes||✓|
--dns-cache-preload||✓|
--egd-file|✓|✓|A Noop for compatibility (GnuTLS can be compiled/configured to use EGD)
--follow-ftp|✓||
--force-atom||✓|
--force-css||✓|
--force-metalink||✓|
--force-rss||✓|
--force-sitemap||✓|
--ftp-password|✓||
--ftps-clear-data-connection|✓||
--ftps-fallback-to-ftp|✓||
--ftps-implicit|✓||
--ftps-resume-ssl|✓||
--ftp-user|✓||
--glob|✓||
--hsts||✓|
--hsts-file||✓|
--hsts-preload||✓|
--hsts-preload-file||✓|
--http2||✓|
--http2-request-window||✓|
--http-proxy||✓|
--https-enforce||✓|
--https-proxy||✓|
--if-modified-since|✓||Wget2 uses If-Modified-Since when timestamping is turned on
--input-encoding||✓|
--input-metalink|✓|(✓)|Wget2 uses a combination of --input-file and --force-metalink
--keep-extension||✓|
--max-threads||✓|
--metalink||✓|
--metalink-over-http|✓||Wget2 does this automatically
--netrc-file||✓|Mainly for test code usage to test .netrc files
--ocsp||✓|
--ocsp-file||✓|
--ocsp-date||✓|
--ocsp-nonce||✓|
--ocsp-server||✓|
--ocsp-stapling||✓|
--passive-ftp|✓||
--preferred-location|✓||Wget2 respects priorities and order of locations
--preserve-permissions|✓||
--proxy-password|✓||
--proxy-user|✓||
--random-file||✓|
--rejected-log|✓||
--relative|✓||
--remove-listing|✓||
--retr-symlinks|✓||
--retry-on-http-status||✓|
--robots||✓|Wget1.x has a robots command but no option, -e robots=1 does the job
--save-content-on||✓|
--show-progress|✓|(✓)|Wget2 has a --force-progress option which is better named
--stats-all||✓|
--stats-dns||✓|
--stats-ocsp||✓|
--stats-server||✓|
--stats-site||✓|
--stats-tls||✓|
--tcp-fastopen||✓|
--warc-cdx|✓||
--warc-compression|✓||
--warc-dedup|✓||
--warc-digests|✓||
--warc-file|✓||
--warc-header|✓||
--warc-keep-log|✓||
--warc-max-size|✓||
--warc-tempdir|✓||
