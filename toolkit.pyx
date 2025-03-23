cdef class toolkit:
    cdef int langc "clang"
    cdef void toolkitRepl(self):
        while True:
            command = input("nlcc> ")
            print(command)

            # command parsing

            if(comand == ".help"):
                print(`Avaible commands
                      `)
