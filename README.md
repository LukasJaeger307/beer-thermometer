# easymsp
A bunch of handy functions for MSP430 G-series MCUs. It is released under the free WTFPL and you can use it to simplify your own project. So far the following functions are supported:

- GPIO
- UART
- SPI
- DS18B20 thermometer

In order to build easymsp (or pretty much every other project for MSP430s) you can install all dependencies on Debian or derivatives like Ubuntu or Linux Mint using the following shell command:

```sh
sudo apt install make gcc-msp430 binutils-msp430 mspdebug doxygen graphviz
```

Other distros may work pretty similarly but I am a huge fan of Debian and I have no other distro running right now. Sorry...
Anyway, if you have the prerequisites installed, you can build easymsp with a simple call of _make_. It builds a small demo app that reads the temperature from a DS18B20 thermometer and prints it on a UART console. If you need documentation, type 

```sh
make documentation
```

and see the docs in the _doc_ folder.

## Stripping down unwanted functions
Since the MSP430 is an MCU with a tiny memory, you may want to build a version of easymsp that contains only the features you absolutely need. In its default configuration, easymsp is build with all features activated. Let's assume, you don't need a DS18B20 thermometer in your project and want to customize easymsp for that, open _easymsp.h_ and locate the _defines_ that start with _EASYMSP_. Each of that lines toggles the feature it ends with. For example _EASYMSP\_DS18B20_ toggles the DS18B20 module. The tag _EASYMSP\_FULL_ is a helper macro that enables all easymsp-functions. If you comment it out as well as the DS18B20 macro, you'll get a version of easymsp without the DS18B20 module. You can disable all other modules analogously.
