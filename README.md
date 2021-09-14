# Operating Systems And Network - Assignment 1
## Name : Chayan Kochar 
## Roll: 2019114008

---
### **Assumptions:**
- Enough space is available on the pc to create and write new files of the same size as of the inout ones.
- I am assuming that the written output appearing in the terminal doesnt matter much ***except the percentage and the permissions of files***. Like for example the program also prints "Reversing task is completed" at the end of task, or say if The folder or some file is not present and we run q3.c, then some error message appears(no specific format told about this), or there is also some new lines inserted. I am assuming this wont be negatively taken into account. All other specifics mentioned have been followed as told.
**Also, there has been many talks lately about whetehr to print file names or not in q3 output. In one of the clarifications we were told :"2. No need to replace, only printing output_file_1 and output_file_2 are enough." I am assuming this means replacing isn't necessary, but doing it is also fine, as giving it proper file name won't have any issue.**
- As the chunk size taken is around 1-10 Megabytes, whle running program q1 and q2, sufficient main memory should be available.
- As *open* command is being used, there should be execute permission on each directory componenet of the path and finally for the file itself.
- The input files like should have read permissions
- If the "Assignment" folder is already created, it should have appropriate permissions to create/open/write in files in it. For example as the output files will be created in the assignment folder, the folder should have write + execute permissions etc etc
- As string.h was allowed, i have used hte function strcat().
- Though *exit()* was used in tutorials and it just gives a warning on not including stdlib.h, but given that it is not a syscall, i have used return instead.
- The input numbers in q2 is assumed to be single digits as discussed in moodle.

---

### **Comments:** (Following were observed on using a 2.02GB txt file)
- I have included stdlib.h library only for malloc usage.
- It was a tough call to choose the right length of chunk size. As going with very small size(eg - going char by char) would lead to many syscalls and thus latency, and having very large size would be difficult for compiler. Hence by trial and error it was found that any number in order of 10e5, 10e6, 10e7 and even 10e8 were doing the tasks in almost the same time. Keeping in mind that percentage should be updated frequently, I chose the 5*10e6(approx 5MB) length.
- Sometimes it appears that speed is slow and sometimes fast. Actually it takes almost same amount of time, just that the numbers we see might be different. That is nothing but the limit of our eyes and computer's internal working. Say if 1*10e6 length is used, it will print in 0.05% increment but we wont be able to see that...hence it would appear as 2.50%....then 4.31....11.75...etc etc and so on.
- On using the given length size or any of the orders given above, it was found that task was completed in around 11-25 seconds for whole reversal of a 2.02GB file

