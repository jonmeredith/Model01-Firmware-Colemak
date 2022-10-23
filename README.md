# To build

make compile VERBOSE=1
make flash VERBOSE=1

# Issues

Had some problems with the `bin/arduino-cli board list` returning a weird device for the keyboard.
Don't know how I fixed it other than permissiong arduino-cli to listen on mdns port.
Tried holding down PROG later in the process to make it work.

Device has different names when programming... Here is operational

❯ bin/arduino-cli board list
Port                            Protocol Type              Board Name          FQBN                   Core
/dev/cu.Bluetooth-Incoming-Port serial   Serial Port       Unknown
/dev/cu.JDMBFPro                serial   Serial Port       Unknown
/dev/cu.usbmodemCkbio01E1       serial   Serial Port (USB) Keyboardio Model 01 keyboardio:avr:model01 keyboardio:avr

Here is `PROG` mode.

❯ bin/arduino-cli board list
Port                            Protocol Type              Board Name          FQBN                   Core
/dev/cu.Bluetooth-Incoming-Port serial   Serial Port       Unknown
/dev/cu.JDMBFPro                serial   Serial Port       Unknown
/dev/cu.usbmodemkbio011         serial   Serial Port (USB) Keyboardio Model 01 keyboardio:avr:model01 keyboardio:avr

Tried setting to prog mode using .envrc
