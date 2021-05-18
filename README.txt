NAME
	late - Live Appending Text Editor

DESCRIPTION
	`late` is a simple, extensable text stream viewer and editor. It will print
	the live appends similar to `tail -f` and allow you to `type stuff [enter]'
	and append to the file.

	This program is designed to be a client for my chat program `ch` but it
	can also work with any other file-based message program - such as suckless ii.

SYNOPSIS
	late [read file] [write file]

EXAMPLES
	ch: late ./chat.txt ./chat.txt	// reads from chad.txt and writes to chat.txt
	ii: late ./out      ./in	// reads from the out file and writes to the
					   in file
