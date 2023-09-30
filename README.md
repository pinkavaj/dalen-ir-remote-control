# Dalen LED light IR remote controll protocol

Describe protocol used for cotrolling of Dalen LED light using infrared
remote cotroller.

The attached Arduino project transmits those commands on arduino pin 3.
The commands are transmited by sending appropriate letter on Rx pin using
9600 baud rate. Send 'h' for help.

* modulation frequency: 38000 Hz
* start: 3.5 ms on, 1.65 ms off
* bit: 422 us (on = 1 or off = 0) + 422 us off

## List of commands
COMMAND (UART letter to run the command) = pulse sequence

Off (f)         = start + 110110110110111101101011011110101011011011010111111111111011111110111110111011110101101
On (o)          = start + 110110110110111101101011011110101011011011010111111111110110110101011011111011101111011011
Bright (b)      = start + 110110110110111101101011011110101011011011010111111111110111010111101111101110111101111
Dim (d)         = start + 110110110110111101101011011110101011011011010111111111110111110111011111011101111101101
Cool (c)        = start + 11011011011011110110101101111010101101101101011111111111011011011101011111011101111011011
Warm (w)        = start + 110110110110111101101011011110101011011011010111111111110110111110101111101110111111011
Whole Light (l) = start + 1101101101101111011010110111101010110110110101111111111101111111101111101110111111101
Night Light (n) = start + 11011011011011110110101101111010101101101101011111111111011011011110111110111011110110101
Glare Free (g)  =  start + 11011011011011110110101101111010101101101101011111111111011110101110111110111011110101011
Sleep (s)       = start + 1101101101101111011010110111101010110110110101111111111101111110110111110111011111101010
