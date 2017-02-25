# sortList
Wordlist management tool

## Features  
* Join multiple wordlists together, checking for duplication of words
* Any URLs in the wordlist can be broken into seperate words (inbetween the slashes) which are then added to the wordlist
* Sort outputted wordlist in ASCII order
* Remove file extensions  

## Usage
```
Usage: sortlist -s -f -e -d /myWordlistFolder  -o /outputdir/outputfile
Options:
	   	All options check for and duplicates in the wordlist
	-h 	Show this help message
	-d 	Directory where wordlists are stored
	   	(Allowed extenstions: .txt & .wordlist & .list)
	-o 	File to output as
	-s 	Sorting in ASCII order (by first character of word)
	-f 	Format lines that contains deeper than one directory
	   	(Adds deeper directories to wordlist as well)
	-e 	Remove file extensions
```
## Installation using Script (WIP)
From the root of the extracted download, execute:
```
sudo chmod +x ./install.sh
sudo ./install.sh
```
## Compiling Manually
From the root of the extracted download, execute:  
`g++ sortList.cpp input.cpp -o sortlist`
