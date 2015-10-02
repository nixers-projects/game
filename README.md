game
====

A game made by members of [nixers](http://nixers.net). The current plan is a
"top-down RPG with a cyberpunk setting". We are writing it in C and SDL. We
have a forum thread [here](http://nixers.net/showthread.php?tid=1621), and
regularly discuss development over at [#game](irc://irc.nixers.net/#game) on
irc.nixers.net.

Dependencies
------------

* [tmx](https://github.com/baylej/tmx), which depends on
  * zlib
  * jansson
  * libxml2
* sdl2 (might as well get the whole suite)

Building
--------

To build the project, simply use

```Bash
make
```

And run the binary

```Bash
./game
```

The name of the binary is subject to change, and we'll add install/deinstall
targets in the future, so keep an eye out.

Contributing
------------

Generally we advise people make forks and pull requests. It allows us to
discuss changes before it's too late and means we won't have issues with conflicting commits. Be sure to
hop on IRC for the most up-to-date discussions.

Style
-----

The `prettify` script uses [astyle](http://astyle.sourceforge.net) to
automatically format the code, please use it. We will reject or at least ask
you to run astyle on any pull requests that are not formatted correctly.
