# AntiqSH

Pronounced - antqiu(e)-sh

An anagram of Tanishq ;)


My attempt at making a simple shell from scratch.

Running: `clear && make && ./antiqsh`

## Directory Structure
```
.
├── antiqsh
├── headers
│   ├── all.h
│   ├── misc.h
│   ├── my_command.h
│   └── proc.h
├── keypress.c
├── Makefile
├── README.md
├── src
│   ├── baywatch.c
│   ├── bg.c
│   ├── cd.c
│   ├── echo.c
│   ├── fg.c
│   ├── handle_child.c
│   ├── handle_command.c
│   ├── handle_input.c
│   ├── handle_io.c
│   ├── handle_my_command.c
│   ├── jobs.c
│   ├── ls.c
│   ├── main.c
│   ├── obj
│   ├── path_utils.c
│   ├── pinfo.c
│   ├── pipe.c
│   ├── procs.c
│   ├── prompt.c
│   ├── pwd.c
│   ├── redirect.c
│   ├── repeat.c
│   ├── replay.c
│   └── sig.c
└── test.txt
```

## Assumptions
- Current path length: 255 characters max. Rest is truncated. 
- Max number of args is 15.
- Max input length for each ';' separated command: 256
- repeat count should be <=15
- max directories ls can show is 4
- max proc name: 255 chars
- max # of proccesses: 255
- for replay command
    - interval range is 1 to 10 and period range is 1 to 10
    - max command len inside replay is max input length (given in pt3 above)
- baywatch follows same interval range for replay, 1 to 10
All these assumptions can be changed in the "all.h" header file

## Resources
### Makefile
- https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
### Prompt
- hostname: https://man7.org/linux/man-pages/man2/gethostname.2.html
### User input
- taking input: good list of functions with good details: https://www.studymite.com/blog/strings-in-c
- tokenize string: https://man7.org/linux/man-pages/man3/strtok_r.3.html
- prepping for execution: https://man7.org/linux/man-pages/man2/fork.2.html
### BG proc
- basic (takes a lot of time to digest, but is the most complete): https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
- wait, waitpid:
    - https://man7.org/linux/man-pages/man2/wait.2.html
    - https://www.dreamincode.net/forums/topic/406981-running-background-process-in-c-using-fork/
    - https://stackoverflow.com/questions/28457525/how-do-you-kill-zombie-process-using-wait
    - example: http://www.cs.ecu.edu/karl/4630/sum01/example1.html
    - v good on WNOHANG: https://stackoverflow.com/questions/33508997/waitpid-wnohang-wuntraced-how-do-i-use-these/34845669
    - introduced SIGCHLD: https://stackoverflow.com/questions/35465758/wait-until-all-background-jobs-have-terminated-c
- signals:
    - https://www.gnu.org/software/libc/manual/html_node/Job-Control-Signals.html
    - https://tildesites.bowdoin.edu/~sbarker/teaching/courses/systems/18spring/lectures/lec24.pdf
    - https://linuxhint.com/signal_handlers_c_programming_language/
- sig handling:
    - http://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/install.html
    - https://stackoverflow.com/questions/21180857/installing-signal-handler-in-c
- setpgid
    - https://man7.org/linux/man-pages/man2/setpgid.2.html
    - https://stackoverflow.com/questions/6025673/why-is-there-timing-problem-while-to-fork-child-processes

## pinfo
- getpid: https://man7.org/linux/man-pages/man2/getpid.2.html
- proc: https://man7.org/linux/man-pages/man5/proc.5.html
- exe file path: https://stackoverflow.com/questions/933850/how-do-i-find-the-location-of-the-executable-in-c
- readlink: https://man7.org/linux/man-pages/man2/readlink.2.html

## piping
- pipes: https://tldp.org/LDP/lpg/node11.html
- dup: https://pubs.opengroup.org/onlinepubs/009695399/functions/dup.html

## bg/fg, sus, signal & continue 
- use previously used commands
- kill: https://man7.org/linux/man-pages/man2/kill.2.html
- signals: https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf
    - 18: sigcont
    - 19: sigstop
    - 9: sigkill
    - 2: sigint

## pipe
- pseudo code for the logic flow: https://stackoverflow.com/questions/916900/having-trouble-with-fork-pipe-dup2-and-exec-in-c/
- v. good example: https://man7.org/linux/man-pages/man2/pipe.2.html
- good pic: https://linuxhint.com/using_pipe_function_c_language/
- https://man7.org/linux/man-pages/man2/dup.2.html

## Baywatch (new born)
- https://man7.org/linux/man-pages/man5/proc.5.html, `/proc/loadavg`
- for the "take input until q thingy": https://man7.org/linux/man-pages/man2/select.2.html
