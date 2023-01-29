# PHide : Process Hider #

This is a simple rootkit that hides a process given its pid from tools like ps,
top, ls... The pid must be specified in the source code or via the command line when loading the rootkit

More information : https://yassine.tioual.com/index.php/2017/01/10/hiding-processes-for-fun-and-profit/

## Compilation ##
```
	$ make
```

## Installation ##
```
	$ sudo insmod phide.ko
	or
	$ sudo insmod phide.ko proc_to_hide="1"
```

## Removal ##
```
	$ sudo rmmod phide
```

## Disclaimer ##

This is an experimental rootkit. Use it at your own risks.
