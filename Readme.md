# HolyC compiler

Variation to the C programming native to [TempleOS](https://templeos.org/).
A recreation of the x64 compiler using C.
This recreation will allow for HolyC to be usable outside TempleOS

## Note
- This will not produce 1:1 assembly or machine code to the compiler found in the kernel.
- This tool will allow the compiling of HolyC.

```holyc
/* Entry point */
I32 demo()
{
    return 1; 
}

/* Everything outside a function gets run */
demo; 
demo;

```
