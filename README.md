# simuart
A demonstration of using the MPLAB X simulator with a simulated UART capturing output to a window or file

This is intended to serve as a demonstration of simulator UART I/O

This might be useful for running tests, the output can be captured to a file and the input can be driven
from a stimulus file enabling multiple tests to be run without the need to "bake" them into the program
although it may be sufficient to bake in the tests and just capture the output.

For simulation purposes the UART does not have a baud rate and as far as I can see will not throw errors
so the error handling is commented out.

I'm not using interrupts as the usage I'd envisage would run synchronously with input...processing...output.
It should be easy enough to add a recieve interrupt though.
