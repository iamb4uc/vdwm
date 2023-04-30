dwm is an extremely fast, small, and dynamic window
manager for X.

This is my current build that I personally use and
dont plan on moving to other WM or DEs. And is
based on the concept of "productivity over looks and bling".
Sure It might not be the best looking or even
working dwm or other wm but with this you will
never need a mouse for your workflow, everything is
perfectly useable when combined with the
[dotfiles](https://github.com/iamb4uc/dots.git) I have.

Requirements
------------
Install these packages:

```sh
xbps-install libX11 libXft libXinerama libX11-devel libXft-devel libXinerama-devel
```


Installation
------------
Edit config.mk to match your local setup (dwm is
installed into the /usr/local namespace by default).

**No need to edit if you use VOIDLINUX**

Afterwards enter the following command to build and install dwm (if
necessary as root):

```sh
make clean install
```

Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:
```sh
exec dwm
```
This uses a autostart script from the directory ~/.local/share/dwm/autostart.sh
so be sure to make that file and make it executable using `chmod +x`.

You can find an example of this script [here](https://github.com/iamb4uc/dots/blob/main/.local/share/dwm/autostart.sh)

Also, this works very well when used with my
[dots](https://github.com/iamb4uc/dots.git)
[st config](https://github.com/iamb4uc/st.git)
[dmenu config](https://github.com/iamb4uc/dmenu.git)
and lastly my
[slstatus config](https://github.com/iamb4uc/slstatus.git) 
