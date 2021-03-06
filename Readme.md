fastpurge
=========

easily purge all keys matching one or more regexes from one or more redis or varnish instances


Usage
-----

```
fastpurge [-xdvhs] [--redis|--varnish SERVER]... [OPTIONS]... [PATTERN]...
  
  -x, --regex
    use regexes instead of plain keys       

  -d, --dry-run
    print the matching keys, but do not delete    

  -s, --silent
    don't print the matching keys

  -v, --version
    print version and exit

  -h, --help 
    print this message and exit


Adapters:

  --redis=HOST(:PORT) 
    purge from redis HOST (multiple allowed)

  --varnish=HOST(:PORT) 
    purge from varnish HOST (multiple allowed)


Redis options:

  --hdel=HASH
    delete keys from hash HASH

  --sdel=SET
    delete keys from set SET

  --zdel=SET
    delete keys from sorted set SET

  --rdb=DB
    use redis database number DB (default is zero)
```


Installation
------------

requires gcc >= 4.6

```
git clone git@github.com:paulasmuth/fastpurge.git
./autogen.sh && make
sudo make install
```

Examples

--------

delete all redis keys matching one of the two regexes

```
fastpurge --regex --redis=10.0.0.1:6379 "key([0-9]+)" "other_key([0-9]+)"
```

delete all keys from hash "foobar:myhash" matching two regexes

```
fastpurge --regex --redis=10.0.0.1:6379 --hdel="foobar:myhash" "key([0-9]+)" "other_key([0-9]+)"
```

delete three redis keys from multiple servers

```
fastpurge --redis=10.0.0.1:6379 --redis=10.0.0.2:6379 key1 key2 key3
```



License
-------

Copyright (c) 2011 Paul Asmuth

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to use, copy and modify copies of the Software, subject 
to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
