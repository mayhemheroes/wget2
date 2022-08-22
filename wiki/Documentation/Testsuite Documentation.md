# HTTP/2 Testsuite Documentation

This document explains how to use the new test suite which extends support for 'h2' testing.

## Changes
### Added
1. **int** h2_server_port<br/>
   Stores 'h2' server's port.<br/>
2. **struct MHD_Daemon** h2daemon<br/>
   Stores h2 daemon<br>
3. **enum** PASS proto_pass<br/>
   **Values:**<br/>
   > HTTP_1_PASS = 0<br/>
   > H2_PASS = 1<br/>
   > END_PASS = 2<br/>
   This variable controls the PASSES through which a test goes through.
4. **int** wget_test_get_h2_server_port(void)<br/>
   > Returns 'h2' server's port if the server is running<br/>
   > Otherwise, returns `-1`.

### Modified
1. **enum** SERVER_MODE<br>
   Added `HTTPS_MODE=1`
2. **int** wget_test_get_http_server(void)<br>
   > Returns http/h2 server's port depending on `proto_pass`
3. **int** wget_test_get_http2_server(void)<br>
   > Returns https/h2 server's port depending on `proto_pass`
4. **const char** \*_parse_hostname(const char \*data)<br>
   > Removes hostname from `data` and returns.<br>
   > If hostname is not present, returns `data` as it is.
