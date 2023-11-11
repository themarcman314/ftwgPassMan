# Faster Than Whai's Grandma or FTWG Password Manager
Hi Pietro, this is an 1000x improvement over last version

Have fun :)

Constructive and destructive criticism is ofc welcome!

This program is intended for linux although could be fun to expand it to other platforms after adding more features

The program is very simple just specify two arguments so even your grandma can run it

The first is one or several letters specifying what character types you want your password to contain
such as:

- u for uppercase 
- l for lowercase
- n for numbers
- s for special characters 

The second argument is the size of the password in characters

Example: (Generates a 10 character password with uppercase characters only)
```console
[marcman@speeddemon ~/[...]/ftwgPassMan]$ ./ftwgpm u 10
Generated password: YTDZOSZTKS
```
Specified password types can also be combined

Example: (Generates a 100 character password will uppercase, numbers and special characters
```console
[marcman@speeddemon ~/[...]/ftwgPassMan]$ ./ftwgpm uns 100
Generated password:
7![A079<8P}2VDY<F3T;24GVX17!3ZZOW3%<9D5@N045'DV!1J7:L2SJ5P"0U \L>127RWR0TX_\P&58U3]3T?G0|VW@99BD23GF
```
