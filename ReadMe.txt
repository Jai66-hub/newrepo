1. Run 'make' command to compile the program.
   make
2. Run the program with different options as mentioned below

example options commands with outputs:- 

1:-  ./search 

op:- 
.
        link.txt -> file1.txt
        search
        Makefile
        projects
                project1
                        README
                        projects1.docx
                fread.c
                read.c
                project2
                        project2.docx
                        README
                fwrite.c
        search.c
        testing.c
        file1.txt
        a.out
  
 2:-   ./searcg -S
 op:- 
 .
        link.txt -> file1.txt [13 rw-r--r-- 14-02-2023 14:47:07]

        search  [22600 rwxr-xr-x 14-02-2023 17:40:26]

        Makefile  [75 rw-r--r-- 14-02-2023 15:12:49]

        projects  [0 rwxr-xr-x 14-02-2023 00:49:47]

                project1  [0 rwxr-xr-x 14-02-2023 00:50:08]

                        README  [0 rw-r--r-- 08-02-2023 17:58:50]

                        projects1.docx  [0 rw-r--r-- 08-02-2023 17:59:01]

                fread.c  [2 rw-r--r-- 08-02-2023 17:58:17]

                read.c  [0 rw-r--r-- 08-02-2023 18:00:13]

                project2  [0 rwxr-xr-x 14-02-2023 00:50:08]

                        project2.docx  [0 rw-r--r-- 08-02-2023 17:59:56]

                        README  [0 rw-r--r-- 08-02-2023 17:59:47]

                fwrite.c  [2 rw-r--r-- 08-02-2023 17:58:27]

        search.c  [8343 rw-r--r-- 14-02-2023 17:38:02]

        testing.c  [6647 rw-r--r-- 14-02-2023 17:14:12]

        file1.txt  [13 rw-r--r-- 14-02-2023 14:47:07]

        a.out  [22600 rwxr-xr-x 14-02-2023 16:17:23]
        
 3.  ./search -s 23
 
 .
        link.txt -> file1.txt

                        README

                        projects1.docx

                fread.c

                read.c

                        project2.docx

                        README

                fwrite.c

        file1.txt

4. ./search -f ead 1

.
                fread.c

                read.c

5. ./searcg -t d

.
        projects

                project1

                project2
5. ./search -t d -S

.
        projects  [0 rwxr-xr-x 14-02-2023 00:49:47]

                project1  [0 rwxr-xr-x 14-02-2023 00:50:08]

                project2  [0 rwxr-xr-x 14-02-2023 00:50:08]


