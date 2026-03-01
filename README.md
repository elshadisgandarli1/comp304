# Shell-ish OS Project
**GitHub Repository:** https://github.com/elshadisgandarli1/comp304

## How to Compile and Run the Shell
1. Compile the main shell: `gcc main.c -o shell`
2. Run the executable: `./shell`
3. You can execute standard UNIX commands, pipe commands together, and use background processes.


# Custom Command: `tree`

The `tree` command is a visual tool that maps out your folders. Normally, if you type `ls`, you only see a flat list of the files right in front of you. 

If you type `./tree`, the program dives into your current folder, looks inside every single sub-folder, and draws a clean, indented "tree" showing exactly how your files are organized from top to bottom. 

## How it works
This command is written in C and uses the `<dirent.h>` library to read folders. 
- It opens a folder and reads every item inside it one by one.
- It intentionally skips the hidden `.` (current) and `..` (backwards) links so the program doesn't get trapped in an infinite loop.
- If it sees a regular file, it prints the name. 
- If it sees another folder, it uses **recursion**. It calls its own function again to step inside that new folder, adding 4 spaces of indentation for every level it goes down. This creates the visual branches (`|__`).

## How to use it

**1. See your current folder:**
If you run it by itself, it maps out the folder you are currently standing in.
`$ ./tree`

**2. See a specific folder:**
If you give it a path, it will map out that specific folder without you needing to `cd` into it first.
`$ ./tree /tmp`

**Example Output:**
.
/tmp
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-fwupd.service-ayhGvI
    |__ .X1-lock
    |__ .X0-lock
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-spice-vdagentd.service-HPxPIF
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-power-profiles-daemon.service-vaeLIu
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-upower.service-44RtkA
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-colord.service-Yt2oaW
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-ModemManager.service-ZQ2OrJ
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-systemd-logind.service-7hHqA7
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-switcheroo-control.service-ScD1SL
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-polkit.service-sXLcPM
    |__ systemd-private-676599d4c7784f91aa34a64b58b4764b-chrony.service-KzlkXk
    |__ .font-unix
    |__ .XIM-unix
    |__ .ICE-unix
    |__ .X11-unix
        |__ X1
        |__ X0
    |__ snap-private-tmp

