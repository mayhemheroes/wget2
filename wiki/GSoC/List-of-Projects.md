# List of Projects for Google Summer of Code

This page will always list open projects for the next Google Summer of Code or other relevant events. If you would like to look at the projects from the previous years, look under the "Project-Archive" directory.

If you're interested in any of the below projects, please talk to us! You can comment on the linked Issue here, or drop us an email on [wget-dev@gnu.org](mailto:wget-dev@gnu.org). Remember, you can also propose a new project that is not on this list. We are always happy to consider new and interesting ideas.


List of Potential Projects:

* [HTTP/2 Test Suite](#http2-test-suite)
* [Support for QUIC](#support-quic-protocol)


## HTTP/2 Test Suite
### Brief Explanation
[HTTP/2](https://tools.ietf.org/html/rfc7540) is a new version of the HTTP protocol for communicating on the web. Wget2 supports downloading using HTTP/2 through the [`nghttp2`](https://nghttp2.org/) library.

However, there exist no tests in the Wget2 test suite for HTTP/2 connections. The aim of this GSoC project would be to add HTTP/2 related tests. The current test suite uses GNU Libmicrohttpd, a lightweight HTTP(S) server which supports only HTTP/1.1. So, you will have to use a different C library for setting up the HTTP/2 tests.

### Expected Results
At the end of this project, there should be a functioning HTTP/2 test suite for Wget2 and the relevant existing tests should be modified so that they run both HTTP/1.1 and HTTP/2.

### Prerequisites
The only prerequisite for this project is a some familiarity with programming in C.

### Relevant Issues
None

### Links / Documentation
- [HTTP/2](https://tools.ietf.org/html/rfc7540)
- [`nghttp2`](https://nghttp2.org/)

### Potential Mentors
Darshit Shah, Tim Rühsen


## Support QUIC Protocol (not for GSOC in 2019 since the spec hasn't ben finalized yet)

### Brief explanation
QUIC is the new standard called to replace HTTP/2. It features stream- and connection-based flow control and authenticated and encrypted payloads. QUIC achieves its full potential by running on top of UDP. For the latter requisite, it relies heavily on DTLS 1.3.

### Expected Results
At the end of the project, there is support in libwget to make a connection using QUIC and there is corresponding support in the Wget2 client.

### Prerequisites
We only expect some familiarity working with C.

### Links / Documentation
- [Overview of QUIC](https://www.chromium.org/quic)
- [An Introduction to QUIC](https://blog.cloudflare.com/the-road-to-quic/)
- [QUIC Protocol](https://tools.ietf.org/html/draft-ietf-quic-transport-15)

### Relevant Issues
None

### Potential Mentors
Tim Rühsen, Darshit Shah, Ander Juaristi

