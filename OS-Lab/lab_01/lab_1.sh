# all in one
find . -type f -name "*.txt" | grep -E "[0-9]+" | grep -E "^[^aeiouAEIOU].{3,}"
# [^aeiouAEIOU] - any character except a, e, i, o, u, A, E, I, O, U 

# Individually:
# a. has the extension .txt.
find . -type f -name "*.txt"
# b. containing atleast one digit
find . -type f -name "*[0-9]*"
# c. having minimum length of 4
find . -type f -name "????*"
# d. does not contain any of the vowels as the start letter
find . -type f -name "[^aeiouAEIOU]*"