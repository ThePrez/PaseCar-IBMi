# PaseCar for IBM i
Utilities to help ILE programs call PASE

## Helper programs

Two helper programs, **BASH** and **BASHJL**, that take a single argument and call a program with bash. If bash isn't available, the default PASE shell will be used. 

```clle
CALL PGM(PASECAR/BASHJL) PARM('echo hello world')
```
## API set

Sorry my documentation is crap. See [the header source code](blob/main/bash/pasecar.h) for some comments
