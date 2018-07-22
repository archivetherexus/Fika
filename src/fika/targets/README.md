# Purpose
The purpose of this directory is to contain all the sub-directories that implement
various targets. These "targets" can be mixed with each other to provide
the correct configuration for your platform. These sub-directories also contain all
the `.cpp` files. Any `.cpp` file that is platform agnostic, should be put inside of
the `common/` directory. 

If you're running linux on x86_64, you'd combine the following targets:
* common
* x86_64
* linux
