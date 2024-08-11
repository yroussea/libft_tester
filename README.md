# small libft tester for 42 student

## how to use

clone it, either in your libft directory or next to it or copy your libft inside the libft_tester directory  
AND name your libft directory "libft"

./tester.sh  [will check all the libft]  
./tester.sh strs mems [will check all the strs/mems fcnt]  
./tester.sh {"type of fcnt"} {"type of fcnt"} {...} [will check all the type you ask for]  
[part1 as type: mems / strs / type]

red means your fcnt doesn't do the job,  
yellow means it does the job but sometimes not like it's suppose to do,  
blue means your file

## to see what test you didn't pass
./show_log.sh {fcnt} {fcnt} {...}  
./show_log.sh error [to see all the test that failed]
