# https://www.hackerrank.com/challenges/validating-credit-card-number/problem

import re
for i in range(int(input())):
    S = input().strip()
    pre_match = re.search(r'^[456]\d{3}(-?)\d{4}\1\d{4}\1\d{4}$', S)
    if pre_match:
        processed_string = "".join(pre_match.group(0).split('-'))
        final_match = re.search(r'(\d)\1{3,}', processed_string)
        print('Invalid') if final_match else print('Valid')
    else:
        print('Invalid')