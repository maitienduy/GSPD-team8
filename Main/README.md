After getting the all the Arduino module wired and code uploaded, pair the Bluetooth of the Arduino with the PC or Ev3 (
default password for Bluetooth module when paring: 1234
After paired, the python server need to know the Serial Bluetooth Port in order get the data
Example: In Windows, when Bluetooth paired, user can find the port in Device manager like the Bluetooth serial at COM4 => changing the port in the python server code (at line 5) to port="COM4"
In Linux system the port look like: /dev/rfcomm0 (after paired, using blueman to active serial device & know the serial port )
In OSX system the port look like: /dev/tty.HC-05-DevB (use ls -lart /dev command to find the right port)
