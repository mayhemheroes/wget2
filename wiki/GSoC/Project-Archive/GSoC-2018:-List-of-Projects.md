This is a tentative list of projects that we have available. Please talk to us (drop us a mail at bug-wget@gnu.org) if you're interested in any of these projects. Also remember, that you can also propose new projects on your own. We are completely willing to take any new / interesting projects up as well.

List of Potential Projects:

* [HTTP/2 Test Suite](#http2-test-suite)
* [JWT and JOSE Support](#jwt-and-jose-support)
* [Support for QUIC](#support-quic-protocol)
* [DNS over HTTP](#adding-support-for-dns-over-http)
* [WARC Library + Integration](#warc-library-and-integration)


## HTTP/2 Test Suite

### Brief Explanation
[HTTP/2](https://tools.ietf.org/html/rfc7540) is a new version of the HTTP protocol for communicating on the web. Wget2 supports downloading using HTTP/2 through the [`nghttp2`](https://nghttp2.org/) library.

However, there exist no tests in the Wget2 test suite for HTTP/2 connections. The aim of this GSoC project would be to add HTTP/2 related tests. The current test suite uses GNU Libmicrohttpd, a lightweight HTTP(S) server which supports only HTTP/1.1. So, you will have to use a different C library for setting up the HTTP/2 tests.

### Expected Results

At the end of this project, there should be a functioning HTTP/2 test suite for Wget2 and the relevant existing tests should be modified so that they run both HTTP/1.1 and HTTP/2.

### Prerequisites

The only prerequisite for this project is a some familiarity with programming in C.

## JWT and JOSE support

### Brief explanation

JSON Web Tokens (JWT) are the new standard way of authenticating access to a RESTful API. While there are lots of frameworks to support JWT-based API development, there are few tools to easily inspect and debug JWT fields.

This project should introduce a new set of functions to libwget capable of handling JWT seamlessly. On our journey, we'll also introduce support for JSON Object Signing and Encryption (JOSE), as JWT is heavily based on it.

### Expected Results

The project should ship two new related but disjoint sets of APIs to libwget: one to work with JWT and another one to automatically encrypt/decrypt/sign/verify (given the proper key) JOSE tokens.

### Prerequisites

We expect candidates to be familiar with the C programming language. Being somewhat exposed to the basics of public and private key cryptography would also help.

## Support QUIC Protocol

### Brief explanation

QUIC is the new standard called to replace HTTP/2. It features stream- and connection-based flow control and authenticated and encrypted payloads. QUIC achieves its full potential by running on top of UDP. For the latter requisite, it relies heavily on DTLS 1.3.

## Adding support for DNS-over-HTTPS

### Brief explanation

DoH is a way to resolve domain names over HTTPS. This for privacy, security and also makes it easy to choose your own resolver.

Draft: https://tools.ietf.org/html/draft-ietf-doh-dns-over-https-02

Info: https://developers.google.com/speed/public-dns/docs/dns-over-https

## WARC Library and Integration

### Brief Explanation

WARC is an internet standard for archiving web pages. Implement a new library from scratch called libwarc that supports all the WARC functionality and then integrate it into libwget and wget.

See: #65 

### Expected Results

A new repository called "libwarc" which allows a user to create and modify WARC archives. Some of the code required for this will be provided, but you must design the entire API for libwarc and deal with the entire GNU Toolchain to make a fully functioning library from scratch. By the end of the project, this library should be available to the public along with integration in libwget and command line arguments for Wget to save warc archives

### Prerequisites

A decent understanding of C will be required for this project. Any experience working with the GNU Toolchain (automake, autoconf, libtool) will be very beneficial, but can be learnt during the project.
