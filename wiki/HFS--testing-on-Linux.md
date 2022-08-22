## Just to test filename decomposition on Mac OSX HFS+

```
$ sudo apt-get install hfsprogs

$ dd if=/dev/zero of=hfsimage bs=512 count=500k
$ /sbin/mkfs.hfsplus hfsimage
$ mkdir mnt
$ sudo mount -o loop -t hfsplus hfsimage mnt
$ sudo chown tim:users mnt

$ cd /mnt
$ git clone git://git.sv.gnu.org/wget.git
$ cd wget
$ ./bootstrap
$ ./configure
$ make 
$ make check
```

Just found a possible bug (unexpected behavior) in HFS+, see [Debian Bug #824743](http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=824743), which breaks tests/test-wget-1.c.