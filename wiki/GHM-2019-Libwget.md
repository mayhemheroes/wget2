# GNU Libwget

## About GNU Libwget
*  Libwget is a HTTP(S) client library + much more
*  LGPL3+
*  Spin-off from GNU Wget2
*  System-independent and portable (backed up by gnulib)
*  Continuously tested on Linux, FreeBSD, MinGW64, OSX, (Solaris from time to time)
*  Continuously fuzzed with ASAN / UBSAN / MSAN with high code coverage
*  Functionality groups also available as separate libraries
*  C API

## Functionality / API groups  1/2
* TCP/IP networking
* DNS + DNS caching
* TLS (GnuTLS, WolfSSL (basic), OpenSSL (basic))
* HTTP + HTTP/2 protocol support (networking / parsing)
* Decompression (gzip, deflate, bzip2, xz, brotli, zstd)
* .netrc database parsing
* XML + HTML scanner (no memory allocations !)
* Atom / RSS scanner
* Hashing (GnuTLS, Nettle, WolfSSL, libgcrypt, gnulib)

## Functionality / API groups  2/2
* CSS parsing
* Metalink parsing
* Sitemap parsing
* Robots.txt parsing
* Pluggable database API for netrc, cookies, HSTS, HPKP, TLS session resumption, OCSP
* Multi-Threading
* Progress bar
* Basic APIs for lists, hashmaps, vectors, MT-safe random, logger, I/O, memory, strings, ... 

## Example sizes of library code
* Built with gcc -Os and ld’s as-needed flag
* 388k for all (libwget.so)
* 14k for the XML + HTML scanner (object file: 4296)
* 35k for the HTTP parser  (object file: 11200)
* 29k for the URL parser incl. utility functions

## Example 1 - GET request
```
uri = wget_iri_parse("http://www.example.org", NULL);
request = wget_http_create_request(uri, "GET");

// here you can set request headers, network options, etc
wget_http_open(&conn, uri);                     // async, returns immediately
wget_http_send_request(conn, request);          // async, returns immediately after write
response = wget_http_get_response(conn);        // returns after response is finished

printf("%s%s\n", response->header->data, response->body->data);
```

## Example 2 - GET request with libwget (simple API)
```
#include <stdio.h>
#include <wget/wget.h>

#define URL "https://example.com/index.html"

int main(void)
{
	wget_http_response *resp;

	// No session needed
	resp = wget_http_get(
		WGET_HTTP_URL, URL,
		// WGET_HTTP_HEADER_SAVEAS_STREAM, stdout,
		0);

	// buffers are always 0 terminated
	if (resp)
		printf("%s", resp->body->data);

	wget_http_free_response(&resp);

	return 0;
}

// real    0m0.335s
// user    0m0.019s
// sys     0m0.003s
// ping is ~130ms
```

## Example 3 - GET request with libcurl (easy API)
```
#include <stdio.h>
#include <curl/curl.h>

#define URL "https://example.com/index.html"

size_t getdata(void *ptr, size_t size, size_t nmemb, void *stream)
{
	fprintf(stream, "%.*s", (int) (size * nmemb), (char *) ptr);

	return size * nmemb;
}

int main(void)
{
	CURL *curl;

	// Session handling is mandatory
	if ((curl = curl_easy_init()) != NULL) {
		char errbuf[CURL_ERROR_SIZE] = "";
		CURLcode code;

		// set options
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getdata);

		code = curl_easy_perform(curl);
		if (code) {
			// error occurred
			fprintf(stderr, "Failed (%d): %s\n", code, errbuf);
		}

		curl_easy_cleanup(curl);
	}

	return 0;
}

// real    0m0.479s
// user    0m0.038s
// sys     0m0.009s
```

## Example 4 - Parsing URLs from HTML

**input**
```html
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  </head>
  <body>
    <link rel="stylesheet" href="test1.css" />
    <img srcset="picture1.png, picture2.png 150w,picture3.png 100x"/>
    <a href="http://example.com/π.txt">first digits of PI</a>
  </body>
</html>
```

**code**
```c
wget_html_parsed_result *parsed  = wget_html_get_urls_inline(data, NULL, NULL);

printf("Encoding '%s'\n", parsed->encoding);

for (int it = 0; it < wget_vector_size(parsed->uris); it++) {
	wget_html_parsed_url *html_url = wget_vector_get(parsed->uris, it);
	wget_string *url = &html_url->url;

	printf("%s.%s '%.*s'\n", html_url->tag, html_url->attr, (int) url->len, url->p);
}
```

**output**
```
Encoding 'UTF-8'
link.href 'test1.css'
img.srcset 'picture1.png'
img.srcset 'picture2.png'
img.srcset 'picture3.png'
a.href 'http://example.com/π.txt'
```

## Example 5 - Hashing

Possible crypto backends
- GnuTLS (libgnutls uses Nettle internally)
- OpenSSL / libcrypto
- WolfSSL
- Nettle
- Gcrypt
- gnulib

**fast hashing (one memory block)**
```
int algo = WGET_DIGTYPE_SHA256;
unsigned char digest[wget_hash_get_len(algo)];

if (wget_hash_fast(algo, plaintext, len, digest) == 0)
  ...

// wget_memtohex(digest, sizeof(digest), out, outsize);
```

**fast convenience function**
```
int algo = WGET_DIGTYPE_SHA256;
int hashlen = wget_hash_get_len(algo);
char a1buf[hashlen * 2 + 1];

// A1BUF = H(user ":" realm ":" password)
wget_hash_printf_hex(algo, a1buf, sizeof(a1buf), "%s:%s:%s", username, realm, password);
```

**stream hashing**
```
int algo = WGET_DIGTYPE_SHA256;
unsigned char digest[wget_hash_get_len(algo)];
wget_hash_hd *handle;

wget_hash_init(&handle, algo);

wget_hash(handle, "123", 3);
wget_hash(handle, "456", 3);

wget_hash_deinit(&handle, digest);
```


## Example 6 - TLS connection
```
tcp = wget_tcp_init();
wget_tcp_set_ssl(tcp, 1); // switch SSL on
wget_tcp_set_ssl_hostname(tcp, host); // enable host name checking
if ((rc = wget_tcp_connect(tcp, host, port)) == WGET_E_SUCCESS) {
  // wget_tcp_write() // wget_tcp_read()

  wget_tcp_close(tcp);
}
wget_tcp_deinit(&tcp);
```
