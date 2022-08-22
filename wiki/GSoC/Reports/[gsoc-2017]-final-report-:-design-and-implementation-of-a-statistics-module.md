**Name** :  
Avinash Sonawane

**Email address**:  
rootkea@gmail.com

**IRC nick**:  
rootkea

**The name of the project**:  
[GNU Wget] Design and implementation of statistics module

**Proposal** :  
https://docs.google.com/document/d/18vdGqP2P7vnqTLbbRxZCbjCHVvjT48x4VXl1nnSej1k/edit?usp=sharing

**Source Code committed**:  
https://gitlab.com/gnuwget/wget2/commits/gsoc-rootkea

---

**Completed**:
* `--stats-dns[=[format:]file]` switch
  1.  [x] DNS resolution duration (in milliseconds) 
  2.  [x] Hostname, IP and Port   
  
Sample run:  
```
$ wget2 --stats-dns=human:stats.txt https://www.gnu.org/philosophy/philosophy.html https://encrypted.google.com
[0] Downloading 'https://encrypted.google.com' ...
[1] Downloading 'https://www.gnu.org/philosophy/philosophy.html' ...
Saving 'index.html.1'
HTTP response 200  [https://encrypted.google.com]
Saving 'philosophy.html.1'
HTTP response 200 OK [https://www.gnu.org/philosophy/philosophy.html]
DNS stats saved in stats.txt
$ cat stats.txt 

DNS timings:
    ms Host
    25 encrypted.google.com:443 (216.58.199.142)
    27 www.gnu.org:443 (208.118.235.148)
```  
* `--stats-tls[=[format:]file]` switch
  1.  [x] TLS version
  2.  [x] TLS Negotiation duration
  3.  [x] TFO
  4.  [x] False Start
  5.  [x] ALPN Protocol used
  6.  [x] Cert Chain size
  7.  [x] TLS resumption

Sample run:  
```
$ wget2 --stats-tls=json:stats.json https://www.gnu.org/philosophy/philosophy.html https://encrypted.google.com
[1] Downloading 'https://www.gnu.org/philosophy/philosophy.html' ...
Saving 'philosophy.html.3'
HTTP response 200 OK [https://www.gnu.org/philosophy/philosophy.html]
[0] Downloading 'https://encrypted.google.com' ...
Saving 'index.html.3'
HTTP response 200  [https://encrypted.google.com]
TLS stats saved in stats.json
$ cat stats.json 
[
	{
		"Hostname" : "www.gnu.org",
		"Version" : "TLS1.2",
		"False Start" : "off",
		"TFO" : "on",
		"ALPN Protocol" : "-",
		"Resumed" : "Yes",
		"TCP Protocol" : "HTTP/1.1",
		"Cert-chain Size" : 2,
		"TLS negotiation duration (ms)" : 442
	},
	{
		"Hostname" : "encrypted.google.com",
		"Version" : "TLS1.2",
		"False Start" : "off",
		"TFO" : "on",
		"ALPN Protocol" : "h2",
		"Resumed" : "Yes",
		"TCP Protocol" : "HTTP/2",
		"Cert-chain Size" : 3,
		"TLS negotiation duration (ms)" : 1034
	}
]

```
* `--stats-server[=[format:]file]` switch
  1.  [x] HSTS
  2.  [x] CSP
  3.  [x] HPKP

Sample run:  
```
$ wget2 --stats-server=human:- https://www.gnu.org/philosophy/philosophy.html https://encrypted.google.com
[0] Downloading 'https://encrypted.google.com' ...
Saving 'index.html.11'
HTTP response 200  [https://encrypted.google.com]
[1] Downloading 'https://www.gnu.org/philosophy/philosophy.html' ...
Saving 'philosophy.html.11'
HTTP response 200 OK [https://www.gnu.org/philosophy/philosophy.html]

Server Statistics:
  encrypted.google.com:
    IP             : 216.58.199.142
    SCHEME         : https
    HPKP           : No existing entry in hpkp db
    HPKP New Entry : No
    HSTS           : No
    CSP            : No

  www.gnu.org:
    IP             : 208.118.235.148
    SCHEME         : https
    HPKP           : No existing entry in hpkp db
    HPKP New Entry : No
    HSTS           : Yes
    CSP            : No

```
* `--stats-ocsp[=[format:]file]` switch
  1.  [x] VALID
  2.  [x] REVOKED
  3.  [x] IGNORED

Sample run:  
```
$ wget2 --stats-ocsp=csv:stats.csv https://www.gnu.org/philosophy/philosophy.html https://encrypted.google.com
[0] Downloading 'https://encrypted.google.com' ...
Saving 'index.html.8'
HTTP response 200  [https://encrypted.google.com]
[1] Downloading 'https://www.gnu.org/philosophy/philosophy.html' ...
Saving 'philosophy.html.8'
HTTP response 200 OK [https://www.gnu.org/philosophy/philosophy.html]
OCSP stats saved in stats.csv
$ cat stats.csv 
Hostname,VALID,REVOKED,IGNORED
encrypted.google.com,2,0,1
www.gnu.org,2,0,0

```
* `--stats-site[=[format:]file]` switch
  1.  [x] No. of docs by status 
  2.  [x] Explicit list of docs by status
  3.  [x] Size of docs (downloaded, decompressed and encryption scheme) 
  4.  [x] References/relationships between docs (links are shown by `--` and redirects are shown with `..`)

Sample run:  
```
$ wget2 --stats-site -r encrypted.google.com
...
Downloaded: 8 files, 80.24K bytes, 9 redirects, 0 errors

Site Statistics:

  https://encrypted.google.com:
    Status    No. of docs
       200              7
         https://encrypted.google.com/robots.txt  1.79K (gzip) : 6.71K (decompressed)
         https://encrypted.google.com/  4.30K (gzip) : 9.71K (decompressed)
         https://encrypted.google.com/images/branding/product/ico/googleg_lodp.ico  1.46K (gzip) : 5.30K (decompressed)
         https://encrypted.google.com/images/branding/googlelogo/1x/googlelogo_white_background_color_272x92dp.png  5.35K (identity) : 5.35K (decompressed)
         https://encrypted.google.com/images/nav_logo229.png  11.98K (identity) : 11.98K (decompressed)
         https://encrypted.google.com/advanced_search?hl=en&amp;authuser=0  47.08K (gzip) : 167.09K (decompressed)
         https://encrypted.google.com/?hl=en  4.30K (gzip) : 9.71K (decompressed)
       301              8
         https://encrypted.google.com/intl/en/policies/privacy/  245  (identity) : 245  (decompressed)
         https://encrypted.google.com/intl/en/about.html  238  (identity) : 238  (decompressed)
         https://encrypted.google.com/setprefdomain?prefdom=IN&amp;prev=https://www.google.co.in/&amp;sig=__L4XlnOQVbvR0sYihWzhttBhEY2w=  338  (identity) : 338  (decompressed)
         https://encrypted.google.com/intl/en/policies/terms/  243  (identity) : 243  (decompressed)
         https://encrypted.google.com/services/  229  (identity) : 229  (decompressed)
         https://encrypted.google.com/language_tools?hl=en&amp;authuser=0  261  (identity) : 261  (decompressed)
         https://encrypted.google.com/intl/en/ads/  232  (identity) : 232  (decompressed)
         https://encrypted.google.com/intl/en/policies/  237  (identity) : 237  (decompressed)

  http://encrypted.google.com:
    Status    No. of docs
       200              1
         http://encrypted.google.com/robots.txt  1.79K (gzip) : 6.71K (decompressed)
       301              1
         encrypted.google.com  226  (identity) : 226  (decompressed)

  http://encrypted.google.com:
encrypted.google.com
|--http://encrypted.google.com/robots.txt
:..https://encrypted.google.com/
|   |--https://encrypted.google.com/images/branding/product/ico/googleg_lodp.ico
|   |--https://encrypted.google.com/intl/en/policies/privacy/
|   |--https://encrypted.google.com/intl/en/about.html
|   |--https://encrypted.google.com/setprefdomain?prefdom=IN&amp;prev=https://www.google.co.in/&amp;sig=__L4XlnOQVbvR0sYihWzhttBhEY2w=
|   |--https://encrypted.google.com/intl/en/policies/terms/
|   |--https://encrypted.google.com/services/
|   |--https://encrypted.google.com/images/branding/googlelogo/1x/googlelogo_white_background_color_272x92dp.png
|   |--https://encrypted.google.com/images/nav_logo229.png
|   |--https://encrypted.google.com/language_tools?hl=en&amp;authuser=0
|   |--https://encrypted.google.com/intl/en/ads/
|   |--https://encrypted.google.com/advanced_search?hl=en&amp;authuser=0
|   |   |--https://encrypted.google.com/intl/en/policies/
|   |   |--https://encrypted.google.com/?hl=en
```
---
**Remaining**:
1.  [ ] test --stats-site with metalink/chunked downloading
2.  [ ] Server response time per document
3.  [ ] wget2_manual.md