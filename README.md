# 1.FlightSim
An airline route simulator.

# 2.Editor 
A program that reads a source file, edits the file based on a second file containing
commands, and then saves the resulting text to a third file.

Commands

There is exactly one space between each element in a command line.
{char} indicates a string of zero or more chars of any length, with spaces allowed.
Line numbers start at zero. The line number of specific text can change during the editing process because of line
insertions and deletions.

Insert
Syntax: I <line#> <position#> {char}
Operation: inserts the char(s) in the line number specified, starting at the position specified.

Replace
Syntax: R <line#> <start_position#> <end_position#> {char}
Operation: replaces the char(s) in the line number specified, between the two positions, inclusive, with the
string specified.

Find
Syntax: F {char}
Operation: Prints the string to screen and follows it with the line numbers of all lines that contain the
specified string, each separated by a single space.

Delete line(s)
Syntax: D <start_line#> <end_line#>
Operation: Deletes the lines specified, inclusive. The text will need to move up to fill the resulting gap.

Erase word(s)
Syntax: E {char}
Operation: removes the specified string from the entire text. If this matches an entire line, then the entire
line should be removed.

Copy and paste
Syntax: C <start_line#> <end_line#> <destination_line#>
Operation: Copies the specified lines and pastes them starting at the destination line number.

Move
Syntax: M <start_line#> <end_line#> <destination_line#>
2.10.2. Operation: Cuts the specified lines and pastes them starting at the destination line number. The
destination line number is based on the original vector before the lines are cut

# 3.Scrabble
A program that reads a file of scrambled 7-letter strings, and then prints out the highest valued
legal Scrabble word(s).
