# FHide : File Hider #

This rootkit is similar to the
[PHide](https://github.com/nisay759/linux-rootkits/tree/master/phide) rootkit.
By default, it hides files beginning with the prefix « rk_ » that are located on the root of
the filesystem « / ». But can be changed on the commandline while inserting the rootkit.

## Compilation ##
```
	$ make
```

## Installation ##
```
	$ sudo insmod fhide.ko
	or
	$ sudo insmod fhide.ko prefix="hideme_" kpath="/tmp/"
```

## Removal ##
```
	$ sudo rmmod fhide
```

## Disclaimer ##

This is an experimental rootkit. Use it at your own risks.
