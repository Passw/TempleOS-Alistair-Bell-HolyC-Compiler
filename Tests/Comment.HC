

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
    /* 
      It's a kayak, not a Titanic -- it will crash if you do something wrong.  You 
      quickly reboot, however.  DOS and the 8-bit home computers of the 80's worked 
      fine without memory protection and most computers in the world -- the embedded 
      ones -- operate without protection.  The resulting simplicity of no protections 
      is why TempleOS has value.  In facts, that's the point of TempleOS.  See the 
      TempleOS Charter.

      Conventional thinking is "failure is not an option" for general purpose 
      operating systems.  Since this OS is used in addition to Windows or Linux, 
      however, failure is an option -- just use Windows or Linux if you can't do 
      something.  I cherry-pick what it will and won't do, to make it maximally 
      beautiful.  The following applications more or less form a basis that spans the 
      range of use that TempleOS is intended for:
    */
    return 1;
}

main;