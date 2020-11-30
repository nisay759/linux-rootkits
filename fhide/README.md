# FHide : File Hider #

#Improved 

Example:
//prefix = the prefix to hide.
//kpath =  the dir to "operte" on / inside of.  Inside this directory the files with the chosen prefix will be hidden.
sudo insmod fhide.ko prefix="_SomeVeryLongPrefix" path="/home/user/"



This rootkit is similar to the
[PHide](https://github.com/nisay759/linux-rootkits/tree/master/phide) rootkit.
It hides files beginning with the prefix « rk_ » that are located on the root of
the filesystem « / »

## Compilation ##
```
	$ make
```

## Installation ##
```
	$ sudo insmod fhide.ko
```

## Removal ##
```
	$ sudo rmmod fhide
```

## Disclaimer ##

This is an experimental rootkit. Use it at your own risks.
