# [HolyC compiler](https://github.com/Alistair-Bell/HolyC-Compiler)

<p align="centre">
<a target="blank"><img src=.github/holyc-logo.svg height="100" width="100" alt="HolyC" /></a>
</p>

Variation to the C programming native to [TempleOS](https://templeos.org/).
A recreation of the x64 compiler using C.
This recreation will allow for HolyC to be usable outside TempleOS

## Note
- This will not produce 1:1 assembly or machine code to the compiler found in the kernel.
- This tool will allow the compiling of HolyC.

```holyc
/* Entry point */
U0 demo()
{
    "Hello World\n";
    return 1; 
}

/* Everything outside a function gets run */
demo; 
demo;

```
