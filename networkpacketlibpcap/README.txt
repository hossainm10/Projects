Hello,

My name is Hossain Mahatheer and I built this Network Packet Sniffer(Imitating Wireshark). This was built using the libpcap library so it can be used on all OS. 
It is much easier to use this library rather than raw sockets. If you want to run this, run the Makefile using "make". A program called "packet_capture" will be created and depending on the OS, you will need to have admin access. I built this on Linux, so I ran "sudo ./capture_packet <interface> packet#". If you download my project in the form it's in, all you need to do is run "make" outside of the header and src folders.

##Note
When it comes to the interface, it depends on your system/OS. This means you need to run ip addr(Linux/MacOS) or ipconfig(Windows)

You may need to also install the libcap library and have your gcc compiler upto date.


