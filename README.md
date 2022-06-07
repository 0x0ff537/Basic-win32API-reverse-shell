# Basic-win32API-reverse-shell

A basic reverse shell using win32 APIs. Connect with the server using a raw socket, then a new cmd.exe process is created and stdin, stdout and stderr are redirected to the socket.
You can use powershell.exe if desired, or make it more stealthy by dynamically resolvig the addresses of the functions. 
