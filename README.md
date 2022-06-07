# Basic-win32API-reverse-shell

A basic reverse shell using win32 APIs. Connect with the server using a raw socket, then a new cmd.exe process is created and stdin, stdout and stderr are redirected to the socket.
You can use powershell.exe if desired, or make it more stealthy by dynamically resolvig the addresses of the functions. 

* Worth to mention that I wrote the code out of some other examples I found on github but can't find them anymore. A good resource if you want to create a more complex reverse shell in assembly can be found [here](https://h0mbre.github.io/Win32_Reverse_Shellcode), written by [h0mbre](https://twitter.com/h0mbre_).
