# Google Summer of Code 2019 Final Report

Wget2 supports both HTTP/1.1 and HTTP/2 protocols, both with and without Transport Layer Security (TLS). The earlier testsuite was able to only test HTTP/1.1. During the project, we added support for h2 (HTTP/2 with TLS) testing. For implementation, we extended the HTTP/1.1 testsuite's interface to h2 protocol. The support for testing HTTP/2 without TLS was not added due to lack of utility. We followed a two-pass approach, we made the existing tests go through both the protocols.

The latter part of the project added support for testing the Online Certificate Status Protocol (OCSP) which is responsible for checking the revocation status of TLS certificates. It allowed checking if Wget2 handles OCSP (Stapled or otherwise) response correctly. It also checks if the client is able to properly communicate with an OCSP Response Server.

## Work Done
Extensions to the testsuite:
1. HTTP/2
2. OCSP Responder
3. OCSP (Stapling)

## Work Left
1. Test OCSP Stapling with revoked response.
2. Test OCSP with caching enabled.

## Change in Code Coverage
**libwget**\
The final measures do not include the increased coverage due to OCSP Stapling.
* Overall: From 73.3% to 77.9%
* libwget/ssl_gnutls.c: From 48.0% to 66.5%
* libwget/http.c: From 54.3% to 79.3%

## HTTP/2 Support
Reference branch: [gsoc-http2-testsuite](https://gitlab.com/gnuwget/wget2/tree/gsoc-http2-testsuite) (merged)

### Changes
**File added**\
tests/test-limit-rate-http2.c

**Changes to the test library**\
Added:
1. **int** h2_server_port
Stores 'h2' server's port.
2. **struct MHD_Daemon** h2daemon
Refers to h2 server's instance.
3. **enum** PASS proto_pass\
This variable controls the PASSES through which a test goes through.\
    Values:
    > HTTP_1_PASS = 0\
    > H2_PASS = 1\
    > END_PASS = 2
4. **int** wget_test_get_h2_server_port(void)
	> Returns 'h2' server's port if the server is running\
	> Otherwise, returns `-1`.

Modified:
1. **enum** SERVER_MODE\
Added new value `HTTPS_MODE`.
2. **int** wget_test_get_http_server(void)\
Returns http/h2 server's port depending on `proto_pass`
3. **int** wget_test_get_http2_server(void)\
Returns https/h2 server's port depending on `proto_pass`
4. **const char** \*_parse_hostname(const char \*data)\
Removes hostname from `data` and returns.\
If hostname is not present, returns `data` as it is.

## OCSP Responder
Reference branch: [gsoc-ocsp-responder](https://gitlab.com/gnuwget/wget2/tree/gsoc-ocsp-responder) (merged)

### Changes
**Files Added**
1. tests/certs/ocsp/README.md\
README for genrating certificates and responses.
2. tests/certs/ocsp/demoCA/*\
Openssl certificate signing records for root and intermediate.
3. tests/certs/ocsp/generate_certs.sh\
Generates certificates.
4. tests/certs/ocsp/generate_resp.sh\
Generates responses.
5. tests/certs/ocsp/interm-template.txt\
Template for intermediate certificate.
6. tests/certs/ocsp/interm.cnf\
Openssl config for intermediate certificate signing.
7. tests/certs/ocsp/root-template.txt\
Template for root certificate.
8. tests/certs/ocsp/server-template.txt\
Template for server certificate.
9. **tests/test-ocsp-server.c**\
Tests OCSP protocol using the added OCSP responder.

**Options added**
1. `--ocsp-date` [Boolean]\
Check if OCSP response is too old. (default: on)

2. `--ocsp-nonce` [Boolean]\
Allow nonce checking when verifying OCSP response. (default: on)

3. `--ocsp-server` [String]\
Set OCSP server address. (default: OCSP server given in certificate)

**Changes to the test library**\
Added:
1. WGET_TEST_FEATURE_OCSP\
Specify whether to use OCSP testing.
```
wget_test_start_server(
    ...,
    WGET_TEST_FEATURE_OCSP,
    ...);
```
2. WGET_TEST_OCSP_RESP_FILE\
Specify which response file the responder should send to the client.
```
wget_test(
    ...,
    WGET_TEST_OCSP_RESP_FILE, "<location to the DER reponse>",
    0);
```
3. **int** wget_test_get_ocsp_server_port()\
Retrieve the port on which the responder is running.
```
printf("Port allocated to OCSP Responder: %d\n", wget_test_get_ocsp_server_port());
```
4. **struct MHD_Daemon** *ocspdaemon\
Refers to OCSP Responder's instance.
5. **gnutls_pcert_st** *pcrt;\
Stores server and intermediate certificate for HTTPS test server.
6. **gnutls_privkey_t** *privkey;\
Stores server key for HTTPS test server.
7. **int** _ocsp_ahc()\
Access Handler Callback for serving OCSP responses.
8. **int** _ocsp_cert_callback()\
Server `pcrt` and `privkey` for the HTTPS server.

Modified:
1. **enum** SERVER_MODE
Added new value `OCSP_MODE`.
2. **char** *_insert_ports()
Added `{{ocspport}}` to refer to OCSP responder's port.

## OCSP (Stapling)
Reference branch: [gsoc-ocsp-stapling](https://gitlab.com/gnuwget/wget2/tree/gsoc-ocsp-stapling) (merged)

### Changes
**Files Added**
1. tests/certs/ocsp/README.md\
README for generating certificates and responses.
2. tests/certs/ocsp/demoCA/*\
Openssl certificate signing records for root and intermediate.
3. tests/certs/ocsp/generate_certs.sh\
Script for generating certificates.
4. tests/certs/ocsp/generate_resp.sh\
Script for generating stapled response.
5. tests/certs/ocsp/interm-template.txt\
Template for intermediate certificate.
6. tests/certs/ocsp/interm.cnf\
Openssl config for intermediate certificate signing.
7. tests/certs/ocsp/root-template.txt\
Template for root certificate.
8. tests/certs/ocsp/server-template.txt\
Template for server certificate.
9. **tests/test-ocsp-stap.c**\
Tests OCSP (stapling) using added server.

**Changes to the test library**\
Added:
1. WGET_TEST_FEATURE_OCSP_STAPLING\
Specify whether to use OCSP (stapling) testing
```
wget_test_start_server(
    ...,
    WGET_TEST_FEATURE_OCSP_STAPLING,
    ...);
```
2. **gnutls_pcert_st** *pcrt_stap\
Stores certificate for HTTPS server
3. **gnutls_privkey_t** privkey_stap\
Stores key for HTTPS server
4. **gnutls_ocsp_data_st** *ocsp_stap_resp\
Stores OCSP Stapled Response
5. **int** _ocsp_stap_cert_callback()\
OCSP stapling certificate callback.

Modified:
1. **enum** SERVER_MODE
Added new value `OCSP_STAP_MODE`.

## Acknowledgement
I'm grateful to my mentors Tim Rühsen and Darshit Shah for their guidance. Their sound knowledge has been a constant source of motivation for me. I'd also like to thank Christian Grothoff (libmicrohttpd), Evgeny Grin (libmicrohttpd), Nikos Mavrogiannopoulos (GnuTLS), Maru Berezin for her work libmicrohttpd-http2, and all of the GNU Community. Google Summer of Code has been a very insightful experience for me and I'm taking away much from it. I'm motivated to keep contributing to the project.
