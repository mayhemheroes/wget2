# Using `ccache`

Installing `ccache` gave me an ~25% speed increase of the `./configure` run:

    time bash ./configure -q
    without `ccache`: real    0m33.464s
    with `ccache`: real    0m25.197s

These timings are 'hot' `./configure` runs.

Make sure that `/usr/lib/ccache` is on your path:

    export PATH="/usr/lib/ccache:$PATH"

If you like colored diagnostics with gcc, add `-fdiagnostics-color=always` to your `CFLAGS`.


# Using `dash`

`Dash` is generally faster than `bash` and is able to run `./configure` scripts.

Be warned that Debian's `dash` has been built without support for `$LINENO`, which makes `./configure` falling back to `bash`. So if you don't experience an increase of speed, check with `dash -c 'echo $LINENO'`. If you just get an empty line, you are struck. I opened [#842242](http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=842242) for discussion.

What I did was (but know what you are doing)

```
apt-get source dash
cd dash-0.5.8/
vi debian/rules (removing --disable-lineno)
LC_ALL=C debuild -b -uc -us
sudo dpkg -i ../dash_0.5.8-2.3_amd64.deb
```

If you forget the LC_ALL=C, you might experience errors regarding the `:` operator when running a configure script.

Now we have ~9% speed gain in comparison with bash.

    time dash ./configure -q
    real    0m22.971s


# If you are stuck with `bash`

The wget2 configure script currently executes `cat` and `rm` both ~2000 times. That are ~4000 forks and execs which sum up to a nice amount of time. To avoid this overhead, you need those commands as 'builtins'.

`bash` supports loadable builtins, on Debian you can install them via `apt-get install bash-builtins`, on other systems you might clone bash sources and compile examples/loadables/. But Debian doesn't include a compiled builtin `cat`, just the source code. Also, there is currently no `rm` module, but I already send a patch for `rm [-rf]` - this will be included in the next bash release.

To enable/load those builtins, it needs the following lines in either the `./configure` script, or into `config.site`:

```
# load rm and cat loadable modules to bash
if [ -n "$BASH" ]; then
  enable -f ~/src/bash/examples/loadables/rm rm
  enable -f ~/src/bash/examples/loadables/cat cat
fi
```

As a reminder how to build bash and the loadables on your own (on Linux amd64):
```
./configure --host=x86_64-pc-linux-gnu --build=x86_64-pc-linux-gnu --without-bash-malloc
make
make loadables
make -C examples/loadables others
```

Now we have ~7% speed gain in comparison with not using builtins.

    time bash ./configure -q
    real    0m23.417s

There is more potential when replacing other often called external commands. I wrote a tool to find out which commands are forked how often and how much CPU time they need: [librusage](https://gitlab.com/rockdaboot/librusage)


# Check your compiler flags

Since there are several hundred calls to the compiler per `./configure` run, the default `CFLAGS` variable should not use optimization. gcc defaults to -O0, but giving that explicitly won't harm.

The above measurements where done with `CFLAGS=-O2 -g`, plus lot's of warning flags from the `manywarnings` gnulib module. Without -O2 this gives me another ~7% gain (not as much as I expected):

    time bash ./configure -q
    real    0m21.876s


# Check your editor / IDE regarding file change notifications

When starting testing, I soon realized that my IDE (Netbeans 8.1) starts parsing the whole project when starting './configure'. Well yes, config.h changed and that IDE starts parsing even when backgrounded. I didn't find a knob to switch it off yet (closed the project for this measurements here). I just mention that because it adds ~75% to slowness to a './configure' run. Other IDE and 'intelligent' editors might behave similar.


# Speeding up `manywarnings` gnulib module

This modules takes a huge amount of this projects `./configure` time. Because it tests each single warning flag (out of a pretty large list) which invokes the compiler each time.

In comparison to our compiler flags hint, we see a ~20% boost.

    time bash ./configure -q --disable-gcc-warnings
    real    0m17.271s

So I replaced the `manywarnings` module with my own version which basically takes advantage of

    gcc -Q --help=warnings,C

Wget2's configure script also checks for `clang` and takes advantage of `-Weverything`.

It takes only ~100ms extra time here when enabled (`touch .manywarnings` and `./configure` again).


# CC/CFLAGS dependent usage of configure caching

In your `~/.bashrc` set CONFIG_SITE like
```
export CONFIG_SITE=~/src/config.site
```

That `config.site` file will now be sourced by each ./configure run.

In the `config.site` add
```
if test "$cache_file" = /dev/null; then
  hash=`echo $CFLAGS $LDFLAGS $host_alias $build_alias|md5sum|cut -d' ' -f1`
  cache_file=~/src/config.cache.$CC.$hash
fi
```

Now, each $CC / $CFLAGS combination uses it's own configure cache.
So you change the compiler and options and still benefit from caching - at least when you do that the second time.
And the caching is system-wide, you benefit even when changing the project.
After updating system headers or dependencies it might be possible that you have remove the cache files in order to regenerate them.
