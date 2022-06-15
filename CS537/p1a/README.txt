Zhiwei Cao
For the project P1a, my idea is use the interaction between file and data
to achieve all instructions. 
For the most of data writing, I used the append to put each data into the 
file. And I also use many read only file to get data that I need and store
in some temperate arrays.

For p instruction:
Read file -> store all (key,value) in a temp array -> store all (key) in 
another temp array -> check if there same (key) -> append new (key,value)
in file -> delete the line have same (key)

For g insturction:
Read file -> store all (key,value) in a temp array -> store all (key) in 
another temp array -> check if there same (key) -> print the (key,value) or Not found

For d insturetion:
Read file -> store all (key,value) in a temp array -> store all (key) in 
another temp array -> check if there same (key) -> delet the line

For c insturetion:
just use "w" tpye of file to rewrite

For a instruction:
Print each line of the file.
