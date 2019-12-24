# Spell Checker

Spell checks text documents faster than a blink of an eye.

This is a very simple **Clang** spell-checker that uses a **Trie data structure**. There are faster implementations, but this is the most space-time efficient one (I guess). 

## Usage
First, execute the `make` command, in order to compile the `.c` files and create the corresponding `executables`: 
```console
make
```

Then, execute `./speller` with a file argument **e.g.**: `file.txt` (path to file):
```console
./speller file.txt
```
And voila! **Here's a sample result**:
```
(...)
AUSITN
vo
---------------------------------

WORDS MISSPELLED:     644
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        19190
-------------
TIME IN load:         0.10s
TIME IN check:        0.01s
TIME IN size:         0.00s
TIME IN unload:       0.06s
TIME IN TOTAL:        0.17s

---------------------------------
```
