docker exec -it postgres-server psql -U postgres
docker exec -it postgres-server psql -U postgres -d userdb

docker run -d \
    --name pg-test-container \
    -e POSTGRES_USER=testuser \
    -e POSTGRES_PASSWORD=mypassword \
    -p 5433:5433 \
    postgres

CREATE DATABASE testdb;

CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password VARCHAR(100) NOT NULL,
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);

CREATE TABLE posts (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    body TEXT NOT NULL,
    author_id INTEGER NOT NULL REFERENCES users(id),
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);

