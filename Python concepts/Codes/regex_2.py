import re
 
"""We create a re.MatchObject and store it in 
   match_object variable
   the '()' parenthesis are used to define a 
   specific group"""
 
match_object = re.match(r'(\w+)@(\w+)\.(\w+)', 'username@geekforgeeks.org')
 
""" w in above pattern stands for alphabetical character
    + is used to match a consecutive set of characters 
    satisfying a given condition
    so w+ will match a consecutive set of alphabetical characters"""
 
# for entire match
print(match_object.group())
# also print(match_object.group(0)) can be used
 
# for the first parenthesized subgroup
print(match_object.group(1))
 
# for the second parenthesized subgroup
print(match_object.group(2))
 
# for the third parenthesized subgroup
print(match_object.group(3))
 
# for a tuple of all matched subgroups
print(match_object.group(1, 2, 3))

print(match_object.groups())