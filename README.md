MY_TAIL_BASIC (by aacar23)

My implementation of tail unix utility

This utility prints given file(s) last 10 lines.
Preceeding each file's output with a header
consisting of file's name if files are more
than one. Otherwise no header printed if no
options that modify this behavior as given.


Options with mandatory arguments needed:

-c / --bytes [byte count]: Print last byte count many characters. 
-n / --lines [line count]: Print last line count many characters. 

Remaining options do not have any parameters:

-v / --verbose: Print file's header no matter the condition. 
-q / --quiet / --silent: Do not print file's header under any condition.


-z / --zero-terminated: Treat '\0' as new line when counting lines for
                        output operation.


--version: Print version number of the utility.
--help: Print help document.

This readme file consists of the same content as the help document.
