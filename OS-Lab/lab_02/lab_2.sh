# To select the lines from a file that have exactly two characters.
grep -E "^\w{2}$" GPL-3
# To select the lines from a file that start with the upper case letter.
grep -E "^[A-Z]\w*" GPL-3
# To select the lines from a file that end with a period.
grep -E "\w*\.$" GPL-3
# To select the lines in a file that has one or more blank spaces.
grep -E "\s{1,}" GPL-3
# To select the lines in a file and direct them to another file which has digits as one of the characters in that line.
grep -E "[0-9]+" GPL-3 > output.txt

# i) Display the number students( only count) belonging to ICT department.
grep -E "ICT" student_information.txt | wc -l
# ii) Replace all occurrences of IT branch with “Information Technology” and save the output to ITStudents.txt
sed -E "s/IT/Information Technology/g" student_information.txt > ITStudents.txt
# iii) Display the average marks of student with the given registration number “1234” (or any specific existing number).
grep -E "1234" student_information.txt | awk -F ":" '{sum=$6+$7+$8; print sum/3}'
# iv) Display the title row in uppercase. The remaining lines should be unchanged.
head -n 1 student_information.txt | tr '[:lower:]' '[:upper:]' > upper.txt && tail -n +2 student_information.txt >> upper.txt

# List all the files containing “MIT” in the current folder. Also display the lines containing MIT being replaced with Manipal Institute of Technology. (Hint: use grep, cut & sed) 
grep -rnw . -e MIT && grep -rnw . -e MIT | cut -f3 -d : | sed 's/MIT/Manipal Institute of Technology/g'

# Write a shell command to display the number of lines, characters, words of files containing a digit in its name
find GPL-3 -type f -name "*[0-9]*" -print0 | xargs -0 wc -l -c -w

# Run wc command in the background many times using wc &. Kill all the processes named wc. 
wc&
ps -aux | grep wc
kill -9 pid_1 pid_2

# Write a sed command that deletes the character before the last character in each line in a file
sed -E 's/.(.)$/\1/' GPL-3

# Write a shell command to count the number lines containing digits present in a file.
grep -E "[0-9]+" GPL-3 | wc -l