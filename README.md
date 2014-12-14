dm36x\_debug\_tools
===================

Useful tools to debug DM365/DM368 chip configuration.
I writed this in hope to determine meanings of GPIOs on TS38F2 IP camera module.


d\_pinmux
---------

Dump `PINMUX0..4` configuration.
See [sprufg5a.pdf][sprufg5a] for details.


d\_gpio
-------

Dump GIO DIR and IN statuses.
Enumeration starts from right to left, top to bottom.
E.g. Bank 0: 0..15, Bank 1: 16..31,
Bank 2: 32..47, Bank 3: 48..63,
Bank 4: 64..79, Bank 5: 80..95,
Bank 6: 96..103.


[sprufg5a]: http://www.ti.com/lit/ug/sprufg5a/sprufg5a.pdf
