

U8 main()
{
    /* 
        TempleOS is a x86_64, multi-cored, non-preemptive multi-tasking, ring-0-only, 
        single-address_mapped (identity-mapped), operating system for recreational 
        programming.  Paging is almost not used.

        The people whom can most benefit are:
          * Professionals doing hobby projects
          * Teenagers doing projects
          * Non-professional, older-persons projects

        Simplicity is a goal to keep the line count down, so it's easy to tinker with.  
        As it turns-out, simplicity makes it faster in some ways, too.  It never 
        switches privilege levels, never changes address maps, tends to load whole 
        contiguous files and other, similar things which boost speed.  It's only 
        119,667 lines of code including the kernel, the 64-bit compiler, the graphics 
        library and all the tools.  More importantly, it's designed to keep the user's 
        line count down -- you can do a Hello World application in one line of code and 
        can put graphics on the scrn with a three line program!
    */
    return 1;
}