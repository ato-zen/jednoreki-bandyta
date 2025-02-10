# One-Armed Bandit
One-Armed Bandit - RTP 95, HF 30

The "One-Armed Bandit" game draws by default 100 thousand rows on five reels from eight digits.

The bet is 100, and the credit is 500 thousand.


All draws and the changing credit value can be saved to a file using the `-file` option.

The return ratio is at the level of 95%.

The hit frequency is 30%.



**Compilation:**

`gcc jb.c -o jb`

**Execution:**

`./jb`

or

`./jb -games 100000 -credit 500000 -file file.txt`

![alt text](https://github.com/ato-zen/jednoreki-bandyta/blob/main/zrzut-ekranu.png?raw=true)
