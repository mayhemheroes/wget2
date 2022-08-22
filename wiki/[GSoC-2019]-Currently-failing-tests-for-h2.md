## Purpose
This document contains a list of the currently failing tests of Wget2 with h2. The test suite used for this is hosted [here](https://gitlab.com/ojhaarjun1/wget2/tree/tmp-http2-testsuite). Please use [this](https://gitlab.com/gnuwget/build-images/blob/master/docker-mhd-http2/Dockerfile) docker image for testing.

## IMPORTANT
We are currently using [libmicrohttpd-http](https://github.com/maru/libmicrohttpd-http2) for testing not libmicrohttpd. Please ensure you have it before you test on this testsuite :)

## Failing Tests

Total number of failures: 7

1. ~~test-p-nc~~ [Bug]  
**Reason for failure:** From manual inspection on some servers which support h2, it was observed that Wget2's `-p -nc` wasn't behaving properly. Success of old test suite is by accident. Issue #451 (fixed)

2. ~~test-metalink~~ [Bug]  
**Reason for failure:** The test is failing due to `--https-enforce=hard` not being able to enforce https on some of the links in the test. Changing these urls from `http://...` to `https://...` fixes the problem.

3. ~~test-bad-chunk~~ [HTTP/2 forbids bad-chunk]  
~~**Reason for failure:** There's a line `failed to receive: 11` in the log. This may be keeping the file 1.bad.txt from being downloaded.~~

4. ~~test--https-enforce-soft1~~  
**Reason for failure:** The current test suite is replacing `{{port}}` with `h2_server_port`. This should be fixed when we implement the Second Pass. As tests with the flag WGET_TEST_HTTP_ONLY, would be automatically skipped for h2 testing.

5. ~~test--https-enforce-soft3~~  
**Reason for failure:** `WGET_TEST_HTTPS_REJECT_CONNECTIONS` preventing fallback to TLS (h2) server.

6. ~~test-gzip~~  
**Reason for failure:** Bug in libwget/http.c. _fix_broken_server_encoding() was called too late.  
**Error in log:** Unexpected content in index.html. Log file contains a line: `Broken server configuration gzip workaround triggered`.

7. ~~test-limit-rate~~  
**Reason for failure:** `failed to receive: 17`. Similar error to test-bad-chunk. (https://gitlab.com/gnuwget/wget2/blob/master/libwget/http.c#L1009)  
**Error in log:** Unexpected content in file1.bin  
**Second issue:** The new timing of wget_test() made the test fail. Fixed by skipping the http/2 test.

8. ~~test-post-handhshake-auth~~  
**Reason for failure:** h2 doesn't support post handshake authentication. The test will be skipped in Second Pass.
