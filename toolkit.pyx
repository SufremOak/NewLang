cimport libc
cimport stdlib
cimport stdio
import subprocess

cdef class toolkit:
    cdef int langc "clang"
    cdef void toolkitRepl(self):
        while True:
            command = input("nlcc> ")
            print(command)

            # command parsing

            if(comand == ".help"):
                print(`Avaible commands

                      .help - show this message
                      .quit - quit this shell
                      `)
            else if(command == ".quit"):
                exit(0)
            else:
                print("No such function or variable.")

    def checkForGcc(self):
        subprocess.run(['gcc', '--version'])
        if(subprocess(exit) == 0):
            print("gcc has been found!")
        else:
            exit(1)
        return gcc

    cdef void compilerJit:
        cdef int jit "python"
        cdef int jitcc NULL

