### t9

Small CLI utility for calculating all possibilities given T9 input.

Does not account for multiple presses... `66` -> `[MNO6][MNO6]` not `N`.

C99 compliant.

```
OPTIONS:
    -i         List entries with their index
    -d         Verify results in wordlist </usr/share/dict/words>
    -df        Same as -d but match full word
    -w <path>  Enable dictionary verification with custom wordlist
    -e <n>     Select the n'th entry in the return list
    -h         Prints help information
```

```
$ t9 -i -df 4355
1:  gell
2:  hell

$ t9 448482
GGTGTA
GGTGTB
... ~4000 entries
44848C
448482

$t9 -e 534 448482
GITHUB
```
