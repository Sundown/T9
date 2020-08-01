**t9**
Small CLI utility for calculating all possibilities given T9 input.

Does not account for multiple presses...
`66` -> `%%` not `N`

```
USAGE:
    t9 [OPTIONS] [INPUT]
OPTIONS:
    -i         List entries with their index
    -d         Verify results in wordlist </usr/share/dict/words>
    -df        Same as -d but match full word
    -w <path>  Enable dictionary verification with custom wordlist
    -e <n>     Select the n'th entry in the return list
    -h         Prints help information
```
