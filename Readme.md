fastpurge
=========

delete all varnish keys by regex(es)

```
fastpurge --varnish -x "key([0-9]+)" "other_key([0-9]+)"
```

delete all varnish keys by key

```
fastpurge --varnish key1 key2 key3 key4 otherkey23
```

delete all redis keys by regex(es)

```
fastpurge --redis -x "key([0-9]+)" "other_key([0-9]+)"
```

delete all redis hash->keys by regex(es)

```
fastpurge --redis -x --hdel "foobar:myhash" "key([0-9]+)" "other_key([0-9]+)"
```

delete all redis keys by key

```
fastpurge --redis key1 key2 key3 key4 otherkey23
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
