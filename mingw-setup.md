# Mingw Setup for Ubuntu 14.04 LTS

The following packages are required:

```sudo apt-get install build-essential mingw-64```

You will also need the 64-bit version of the `GdiPlus.dll` file from a 64-bit version of Windows.

## Setup mingw64

```
sudo ln -s /usr/x86_64-w64-mingw32 /mingw64
cd /mingw64
sudo mkdir bin
cd bin


for f in /usr/bin/x86_64-w64-mingw32-*; do 
    sudo ln -s $f
done


for f in *; do 
    name=`echo $f | awk -F '-' '{print $4}'`
    sudo ln -s $f $name
done

cd ../include
sudo ln -s shlobj.h Shlobj.h
sudo ln -s gdiplus.h GdiPlus.h
sudo cp /path/to/GdiPlus64bit.dll /mingw64/lib
```

> The setup of mingw32 is simliar.  Create the symlink `/mingw32` linking to `/usr/i686-w64-mingw32` and repeat the instructions above for the 32-bit version of mingw.

