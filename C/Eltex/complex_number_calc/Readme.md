# Complex number calculator

Use `make` to compile the program and build the following libraries:
* Static library `build/libstc.a`;
* Dynamic library `build/libdyn.so`;
* Separate libraries `build/plugins/*.so` that keep only one function themselves.

Then run one of the created executable files:
* `main_static.out` - test static lib;
* `main_dynamic.out` - test dynamic lib;
* `main_plugins.out` - test plugins (*in process*).

Use `make clean` if you want to remove all compiled stuff.
