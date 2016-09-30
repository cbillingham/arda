![Arda](/images/arda.png)  

A simple operating system developed from scratch.  

It is based on [littleosbook](http://littleosbook.github.io) and [James Malloy's OS tutorial](http://web.archive.org/web/20101019051118/http://www.jamesmolloy.co.uk/tutorial_html/index.html).  
It is developed in C and x86 Assembly on Ubuntu 14.04. It uses Bochs to simulate hardware.

## Current Stage of Development

Arda was started as a class project but has since turned into a fun side project. A way for me to learn more about OS development. I have been following the chapters of littleosbook's development, but also using Malloy's chapters for reference:

- [X] 1. Booting
- [X] 2. Hello cafebabe
- [X] 3. Getting to C
- [X] 4. Output
- [X] 5. Segmentation
- [X] 6. Interrupts and Input
- [ ] 7. The Road to User Mode
- [ ] 8. Virtual Memory
- [ ] 9. Paging
- [ ] 10. Page Frame Allocation
- [ ] 11. User Mode
- [ ] 12. File Systems
- [ ] 13. System Calls
- [ ] 14. Multitasking

Arda will currently boot, display text, catch segmentation errors and interrupts, and receive keyboard input.

## Set Up

To run or contribute to Arda, you need to be developing on [Ubuntu 14.04](http://releases.ubuntu.com/14.04/) (for consistency sake). An easy way to run Ubuntu on any operating system is to install [Virutal Box](https://www.virtualbox.org/wiki/Downloads) and setup an Ubuntu virtual machine ([easy installation instructions here](http://linus.nci.nih.gov/bdge/installUbuntu.html)).

#### Installing Bochs

Once running Ubuntu, we need to install Bochs. Bochs is an emulator for the x86 (IA-32) platform which is well suited for OS development due to its debugging features. We also need to make sure some basic compilers and other command line tools are installed which help us build the project.

Open terminal and run

```bash
sudo apt-get install build-essential nasm genisoimage bochs bochs-sdl
```

Once you've install these essential tools and Bochs, you can clone this repository to your local Ubuntu machine.

#### Running
Arda uses a Makefile to simplify the building and compiling of assembly and C files. You can examine the Makefile for more details on the build process.  
To run Arda, simply cd into the source directory in this repository and run

```bash
make run
```

