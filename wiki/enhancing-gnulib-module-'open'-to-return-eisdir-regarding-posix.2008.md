## Problem description

During Wget2 development (Building and Testing on MinGW+Wine / Windows) we discovered a slight incompatibility regarding the `errno` value. Regarding [POSIX.2008 open()](http://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html) `errno` should be `EISDIR` when `pathname` is an existing directory *and* `flags` contains either O_RDWR or O_WRONLY.

```
[EISDIR]
    The named file is a directory and oflag includes O_WRONLY or O_RDWR, or includes O_CREAT without O_DIRECTORY.
```

Gnulib's emulation code for Windows returns EACCES instead of EISDIR.

We rely on POSIX.2008 behavior at several places (wget.c and libtest.c) and now have to use the Windows API to make some extra checks. Of course we would like to see the correct behavior in gnulib, so that we do not have to care about it. That's the main reason why we use gnulib. And many other projects also benefit from any gnulib enhancements as well.

## Gnulib integration

While we have the code working for us, the steps to get the code into gnulib have been described in detail by Bruno Haible, maintainer of gnulib:

```
This portability issue is an ideal "skills ramp up" for someone who has only done
smaller contributions to gnulib so far.

Steps:
1) Consider the standards: What does POSIX:2008 say about the issue?
2) Extend the unit test of module 'open'.
3) Ask us to test these extended unit tests on various platforms (Mac OS X, Solaris,
   FreeBSD, HP-UX, etc.).
4) Mention the issue in the doc section about 'open'.
5) Extend the Autoconf test to recognize this case and arrange to override the
   'open' function when the Autoconf test fails.
6) Extend the workaround (lib/open.c) and make sure the unit test now succeeds
   on the relevant platform(s).
```

1) has already been answered.

Maybe we can work on the above step by step. I especially have Juniors / Students in mind who like to experience project-spanning work for their portfolio.

Quick start for gnulib:
- git clone https://git.savannah.gnu.org/git/gnulib.git
- cd gnulib
- ./gnulib-tool --create-testdir --dir=../testdir-open --single-configure open
- cd ../testdir-open
- ./configure CFLAGS=-Wall && make && make check