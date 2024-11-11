# Project: BlogAPI

```
// Project structure:
//
// blogAPI/
// ├── cmd/
// │   └── main.go
// ├── internal/
// │   ├── models/
// │   │   └── user.go
// │   ├── repository/
// │   │   └── user_repository.go
// │   │   └── post_repository.go
// │   ├── handlers/
// │   │   └── user_handler.go
// |   │   └── post_handler.go
// |   │   └── auth_handler.go
// │   └── middleware/
// |       └── auth.go
// |       └── jwt.go
// ├── pkg/
// │   └── utils/
// │       └── password.go
// ├── go.mod
// └── go.sum
```

## Step 1: Creating USER model

```go
// File: internal/models/user.go
package models

import "time"

type User struct {
    ID        int64     `json:"id"`
    Username  string    `json:"username"`
    Email     string    `json:"email"`
    Password  string    `json:"-"`
    CreatedAt time.Time `json:"created_at"`
    UpdatedAt time.Time `json:"updated_at"`
}
```

```go
// File: pkg/utils/password.go
package utils

import (
    "golang.org/x/crypto/bcrypt"
)

func HashPassword(password string) (string, error) {
    bytes, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.DefaultCost)
    return string(bytes), err
}

func CheckPasswordHash(password, hash string) bool {
    err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(password))
    return err == nil
}
```

```go
// File: internal/repository/user_repository.go
package repository

import (
    "database/sql"
    "time"
    "user-service/internal/models"
)

type UserRepository struct {
    db *sql.DB
}

func NewUserRepository(db *sql.DB) *UserRepository {
    return &UserRepository{db: db}
}

func (r *UserRepository) Create(user *models.User) error {
    query := `
        INSERT INTO users (username, email, password, created_at, updated_at)
        VALUES ($1, $2, $3, $4, $5)
        RETURNING id`
    
    now := time.Now()
    return r.db.QueryRow(
        query,
        user.Username,
        user.Email,
        user.Password,
        now,
        now,
    ).Scan(&user.ID)
}

func (r *UserRepository) GetByEmail(email string) (*models.User, error) {
    user := &models.User{}
    query := `SELECT id, username, email, password, created_at, updated_at FROM users WHERE email = $1`
    err := r.db.QueryRow(query, email).Scan(
        &user.ID,
        &user.Username,
        &user.Email,
        &user.Password,
        &user.CreatedAt,
        &user.UpdatedAt,
    )
    if err == sql.ErrNoRows {
        return nil, nil
    }
    return user, err
}
```

```go
// File: internal/handlers/user_handler.go
package handlers

import (
    "encoding/json"
    "net/http"
    "user-service/internal/models"
    "user-service/internal/repository"
    "user-service/pkg/utils"
)

type UserHandler struct {
    userRepo *repository.UserRepository
}

func NewUserHandler(userRepo *repository.UserRepository) *UserHandler {
    return &UserHandler{userRepo: userRepo}
}

type RegisterRequest struct {
    Username string `json:"username"`
    Email    string `json:"email"`
    Password string `json:"password"`
}

func (h *UserHandler) Register(w http.ResponseWriter, r *http.Request) {
    var registerReq RegisterRequest
    if err := json.NewDecoder(r.Body).Decode(&registerReq); err != nil {
        http.Error(w, err.Error(), http.StatusBadRequest)
        return
    }

    hashedPassword, err := utils.HashPassword(registerReq.Password)
    if err != nil {
        http.Error(w, "Error processing password", http.StatusInternalServerError)
        return
    }

    user := &models.User{
        Username: registerReq.Username,
        Email:    registerReq.Email,
        Password: hashedPassword,
		CreatedAt: time.Now().Format(time.RFC3339),
    	UpdatedAt: time.Now().Format(time.RFC3339),
    }

    if err := h.userRepo.Create(user); err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }

    response := map[string]interface{}{
        "id":      user.ID,
        "username": user.Username,
        "email":   user.Email,
        "message": "User created successfully",
    }

    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusCreated)
    if err := json.NewEncoder(w).Encode(response); err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
    }
}
```

```go
// File: cmd/main.go
package main

import (
    "database/sql"
    "log"
    "net/http"
    "user-service/internal/handlers"
    "user-service/internal/repository"

    "github.com/gorilla/mux"
    _ "github.com/lib/pq"
)

func main() {
    // Connect to database
    dsn := "host=localhost user=postgres password=mysecretpassword dbname=userdb port=5432 sslmode=disable"
	db, err := sql.Open("postgres", dsn)
    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    // Initialize repositories and handlers
    userRepo := repository.NewUserRepository(db)
    userHandler := handlers.NewUserHandler(userRepo)

    // Setup router
    r := mux.NewRouter()
    r.HandleFunc("/api/register", userHandler.Register).Methods("POST")

    // Start server
    log.Printf("Server starting on :8080")
    log.Fatal(http.ListenAndServe(":8080", r))
}
```

## Step 2: Creating POST model

```go
// File: internal/models/post.go
package models

import (
    "time"
)

type Post struct {
    ID        int64     `json:"id"`
    Title     string    `json:"title"`
    Body      string    `json:"body"`
    AuthorID  int64     `json:"author_id"`
    Author    *User     `json:"author,omitempty"`
    CreatedAt time.Time `json:"created_at"`
    UpdatedAt time.Time `json:"updated_at"`
}
```

```go
// File: internal/repository/post_repository.go
package repository

import (
	"database/sql"
	"time"

	"github.com/anoying-kid/go-apps/blogAPI/internal/models"
)

type PostRepository struct {
	db *sql.DB
}

func NewPostRepository(db *sql.DB) *PostRepository {
	return &PostRepository{db: db}
}

func (r *PostRepository) Create(post *models.Post) error {
	query := `
		INSERT INTO posts (title, body, author_id, created_at, updated_at)
		VALUES ($1, $2, $3, $4, $5)
		RETURNING id`

	now := time.Now()
	return r.db.QueryRow(
		query,
		post.Title,
		post.Body,
		post.AuthorID,
		now,
		now,
	).Scan(&post.ID)
}

func (r *PostRepository) GetByID(id int64) (*models.Post, error) {
    post := &models.Post{}
    query := `
        SELECT p.id, p.title, p.body, p.author_id, p.created_at, p.updated_at,
               u.username, u.email
        FROM posts p
        JOIN users u ON p.author_id = u.id
        WHERE p.id = $1`
    
    var author models.User
    err := r.db.QueryRow(query, id).Scan(
		&post.ID,
        &post.Title,
        &post.Body,
		&post.AuthorID,
        &post.CreatedAt,
        &post.UpdatedAt,
        &author.Username,
        &author.Email,
    )
    if err == sql.ErrNoRows {
        return nil, nil
    }
    if err != nil {
        return nil, err
    }
    
    author.ID = post.AuthorID
    post.Author = &author
    return post, nil
}

func (r *PostRepository) List(limit, offset int) ([]*models.Post, error) {
    query := `
        SELECT p.id, p.title, p.body, p.author_id, p.created_at, p.updated_at,
               u.username, u.email
        FROM posts p
        JOIN users u ON p.author_id = u.id
        ORDER BY p.created_at DESC
        LIMIT $1 OFFSET $2`
    
    rows, err := r.db.Query(query, limit, offset)
    if err != nil {
        return nil, err
    }
    defer rows.Close()

    var posts []*models.Post
    for rows.Next() {
        post := &models.Post{}
        author := &models.User{}
        
        err := rows.Scan(
            &post.ID,
            &post.Title,
            &post.Body,
            &post.AuthorID,
            &post.CreatedAt,
            &post.UpdatedAt,
            &author.Username,
            &author.Email,
        )
        if err != nil {
            return nil, err
        }
        
        author.ID = post.AuthorID
        post.Author = author
        posts = append(posts, post)
    }
    
    return posts, nil
}

func (r *PostRepository) Update(post *models.Post) error {
    query := `
        UPDATE posts 
        SET title = $1, body = $2, updated_at = $3
        WHERE id = $4 AND author_id = $5`
    
    result, err := r.db.Exec(
        query,
        post.Title,
        post.Body,
        time.Now(),
        post.ID,
        post.AuthorID,
    )
    if err != nil {
        return err
    }
    
    rowsAffected, err := result.RowsAffected()
    if err != nil {
        return err
    }
    if rowsAffected == 0 {
        return sql.ErrNoRows
    }
    
    return nil
}
```

```go
// File: internal/handlers/post_handler.go
package handlers

import (
	"encoding/json"
	"net/http"
	"strconv"

	"github.com/anoying-kid/go-apps/blogAPI/internal/middleware"
	"github.com/anoying-kid/go-apps/blogAPI/internal/models"
	"github.com/anoying-kid/go-apps/blogAPI/internal/repository"
	"github.com/gorilla/mux"
)

type PostHandler struct {
	postRepo *repository.PostRepository
}

type UpdatePostRequest struct {
    Title string `json:"title"`
    Body  string `json:"body"`
}

func NewPostHandler(postRepo *repository.PostRepository) *PostHandler {
	return &PostHandler{postRepo: postRepo}
}

type CreatePostRequest struct {
	Title   string `json:"title"`
	Body    string `json:"body"`
}

func (h *PostHandler) Create(w http.ResponseWriter, r *http.Request) {
    // Get user ID from context
    userID, ok := r.Context().Value(middleware.UserIDKey).(int64)
    if !ok {
        http.Error(w, "Unauthorized", http.StatusUnauthorized)
        return
    }
	var req CreatePostRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	// authorID := int64(1) // Replace with actual author ID
	
	post := &models.Post{
		Title:     req.Title,
		Body:      req.Body,
		AuthorID:  userID,
	}

	if err := h.postRepo.Create(post); err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }

	w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusCreated)
    json.NewEncoder(w).Encode(post)

}

func (h *PostHandler) Get(w http.ResponseWriter, r *http.Request) {
    vars := mux.Vars(r)
    id, err := strconv.ParseInt(vars["id"], 10, 64)
    if err != nil {
        http.Error(w, "Invalid post ID", http.StatusBadRequest)
        return
    }

    post, err := h.postRepo.GetByID(id)
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }
    if post == nil {
        http.Error(w, "Post not found", http.StatusNotFound)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    json.NewEncoder(w).Encode(post)
}

func (h *PostHandler) Update(w http.ResponseWriter, r *http.Request) {
    userID, ok := r.Context().Value(middleware.UserIDKey).(int64)
    if !ok {
        http.Error(w, "Unauthorized", http.StatusUnauthorized)
        return
    }

    vars := mux.Vars(r)
    postID, err := strconv.ParseInt(vars["id"], 10, 64)
    if err != nil {
        http.Error(w, "Invalid post ID", http.StatusBadRequest)
        return
    }

    existingPost, err := h.postRepo.GetByID(postID)
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }
    if existingPost == nil {
        http.Error(w, "Post not found", http.StatusNotFound)
        return
    }

    // Check if the user is the author
    if existingPost.AuthorID != userID {
        http.Error(w, "Unauthorized: you are not the author of this post", http.StatusForbidden)
        return
    }

    // Decode the update request
    var req UpdatePostRequest
    if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
        http.Error(w, err.Error(), http.StatusBadRequest)
        return
    }

    // Update the post
    existingPost.Title = req.Title
    existingPost.Body = req.Body

    if err := h.postRepo.Update(existingPost); err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    json.NewEncoder(w).Encode(existingPost)
}

func (h *PostHandler) List(w http.ResponseWriter, r *http.Request) {
    limit := 10
    offset := 0

    if limitStr := r.URL.Query().Get("limit"); limitStr != "" {
        if parsedLimit, err := strconv.Atoi(limitStr); err == nil {
            limit = parsedLimit
        }
    }
    if offsetStr := r.URL.Query().Get("offset"); offsetStr != "" {
        if parsedOffset, err := strconv.Atoi(offsetStr); err == nil {
            offset = parsedOffset
        }
    }

    posts, err := h.postRepo.List(limit, offset)
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    json.NewEncoder(w).Encode(posts)
}
```

```go
// File: cmd/main.go
package main

import (
	"database/sql"
	"log"
	"net/http"

	"github.com/anoying-kid/go-apps/blogAPI/internal/handlers"
	"github.com/anoying-kid/go-apps/blogAPI/internal/repository"
	"github.com/gorilla/mux"
	_ "github.com/lib/pq"
)

func main(){
	dsn := "host=localhost user=postgres password=mysecretpassword dbname=userdb port=5432 sslmode=disable"
	db, err := sql.Open("postgres", dsn)
	if err != nil {
		log.Fatal("Fail to connect to the database: ",err)
	}
	// Test the connection
    err = db.Ping()
    if err != nil {
        log.Fatal("Failed to ping database:", err)
    }
    
    log.Println("Successfully connected to database")
	defer db.Close()

	// Initialize repositories and handlers
	userRepo := repository.NewUserRepository(db)
	userHandler := handlers.NewUserHandler(userRepo)

	postRepo := repository.NewPostRepository(db) // New
	postHandler := handlers.NewPostHandler(postRepo) // New

	// Setup router
	r := mux.NewRouter()
	r.HandleFunc("/api/register", userHandler.Register).Methods("POST")
	r.HandleFunc("/api/posts", postHandler.Create).Methods("POST") // New
    r.HandleFunc("/api/posts/{id}", postHandler.Get).Methods("GET")// New
    r.HandleFunc("/api/posts", postHandler.List).Methods("GET") // New

	// Start server
	log.Printf("Server starting on :8080")
	log.Fatal(http.ListenAndServe(":8080", r))
}
```

## Step 3: Adding JWT Authentication

```go
// File: internal/middleware/auth.go

package middleware

import (
	"context"
	"net/http"
	"strings"
)

// Custom type for context keys
type contextKey string

const UserIDKey contextKey = "user_id"

type Claims struct {
	UserID int64 `json:"user_id"`
}

func AuthMiddleware(next http.HandlerFunc) http.HandlerFunc {
    return func(w http.ResponseWriter, r *http.Request) {
        // Get the Authorization header
        authHeader := r.Header.Get("Authorization")
        if authHeader == "" {
            http.Error(w, "Authorization header required", http.StatusUnauthorized)
            return
        }

        // Check if the header starts with "Bearer "
        bearerToken := strings.Split(authHeader, " ")
        if len(bearerToken) != 2 || bearerToken[0] != "Bearer" {
            http.Error(w, "Invalid authorization header format", http.StatusUnauthorized)
            return
        }

        // Validate the JWT token
        claims, err := ValidateToken(bearerToken[1])
        if err != nil {
            http.Error(w, "Invalid token", http.StatusUnauthorized)
            return
        }

        // Add the user ID to the request context
        ctx := context.WithValue(r.Context(), UserIDKey, claims.UserID)
        next.ServeHTTP(w, r.WithContext(ctx))
    }
}
```

```go
// File: internal/middleware/jwt.go
package middleware

import (
	"fmt"
	"time"

	"github.com/golang-jwt/jwt"
)

type JWTClaim struct {
	Claims
	jwt.StandardClaims
}

type TokenPair struct {
	AccessToken  string `json:"access_token"`
	RefreshToken string `json:"refresh_token"`
}

var jwtSecret = []byte("super-secret-key") // In production, use environment variable

func GenerateToken(userID int64) (string, error) {
	claims := &JWTClaim{
		Claims: Claims{UserID: userID},
		StandardClaims: jwt.StandardClaims{
			ExpiresAt: time.Now().Add(time.Hour * 24).Unix(), // 24 hours for access token
			IssuedAt:  time.Now().Unix(),
		},
	}

	// Changed from ES256 to HS256 to match the validation method
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	return token.SignedString(jwtSecret)
}

func GenerateRefreshToken(userID int64) (string, error) {
	claims := &JWTClaim{
		Claims: Claims{UserID: userID},
		StandardClaims: jwt.StandardClaims{
			ExpiresAt: time.Now().Add(time.Hour * 24 * 7).Unix(), // 7 days for refresh token
			IssuedAt:  time.Now().Unix(),
		},
	}

	token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
	return token.SignedString(jwtSecret)
}

func ValidateToken(tokenString string) (*Claims, error) {
	token, err := jwt.ParseWithClaims(
		tokenString,
		&JWTClaim{},
		func(token *jwt.Token) (interface{}, error) {
			// Check if the signing method is what we expect
			if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
				return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
			}
			return jwtSecret, nil
		},
	)

	if err != nil {
		return nil, fmt.Errorf("failed to parse token: %v", err)
	}

	if claims, ok := token.Claims.(*JWTClaim); ok && token.Valid {
		return &claims.Claims, nil
	}

	return nil, fmt.Errorf("invalid token")
}

func GenerateTokenPair(userID int64) (*TokenPair, error) {
	// Generate access token
	accessToken, err := GenerateToken(userID)
	if err != nil {
		return nil, fmt.Errorf("failed to generate access token: %v", err)
	}

	// Generate refresh token
	refreshToken, err := GenerateRefreshToken(userID)
	if err != nil {
		return nil, fmt.Errorf("failed to generate refresh token: %v", err)
	}

	return &TokenPair{
		AccessToken:  accessToken,
		RefreshToken: refreshToken,
	}, nil
}

func ValidateRefreshToken(tokenString string) (int64, error) {
	claims, err := ValidateToken(tokenString)
	if err != nil {
		return 0, fmt.Errorf("invalid refresh token: %v", err)
	}

	return claims.UserID, nil
}
```

```go
// handlers/auth_handler.go

package handlers

import (
	"encoding/json"
	"net/http"

	"github.com/anoying-kid/go-apps/blogAPI/internal/middleware"
)

type AuthHandler struct {}

type RefreshTokenRequest struct {
    RefreshToken string `json:"refresh_token"`
}

func (h *AuthHandler) RefreshToken(w http.ResponseWriter, r *http.Request) {
    var req RefreshTokenRequest
    if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
        http.Error(w, "Invalid request body", http.StatusBadRequest)
        return
    }

    // Validate the refresh token
    userID, err := middleware.ValidateRefreshToken(req.RefreshToken)
    if err != nil {
        http.Error(w, "Invalid refresh token", http.StatusUnauthorized)
        return
    }

    // Generate new token pair
    tokens, err := middleware.GenerateTokenPair(userID)
    if err != nil {
        http.Error(w, "Failed to generate new tokens", http.StatusInternalServerError)
        return
    }

    w.Header().Set("Content-Type", "application/json")
    json.NewEncoder(w).Encode(tokens)
}
```

```go
// File: internal/handler/post_handler.go

type PostHandler struct {
	postRepo *repository.PostRepository
}

// New
type UpdatePostRequest struct {
    Title string `json:"title"`
    Body  string `json:"body"`
}

func NewPostHandler(postRepo *repository.PostRepository) *PostHandler {
	return &PostHandler{postRepo: postRepo}
}
// Same

func (h *PostHandler) Create(w http.ResponseWriter, r *http.Request) {
    // Get user ID from context
    userID, ok := r.Context().Value(middleware.UserIDKey).(int64) // New
    if !ok {
        http.Error(w, "Unauthorized", http.StatusUnauthorized)
        return
    } // New
	var req CreatePostRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	// authorID := int64(1) // Replace with actual author ID // New

	post := &models.Post{
		Title:     req.Title,
		Body:      req.Body,
		AuthorID:  userID, // New
	}

	if err := h.postRepo.Create(post); err != nil {
```

```go
// File: internal/handler/user_handler.go

// Add these in user_handler.go
type LoginRequest struct {
    Email    string `json:"email"`
    Password string `json:"password"`
}
func (h *UserHandler) Login(w http.ResponseWriter, r *http.Request) {
	var req LoginRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}
	// Get user by email
	user, err := h.userRepo.GetByEmail(req.Email)
	if err != nil {
		http.Error(w, "Invalid email or password", http.StatusUnauthorized)
		return
	}
	if user == nil {
		http.Error(w, "Invalid email or password", http.StatusUnauthorized)
		return
	}
	// Verify password
	if !utils.CheckPasswordHash(req.Password, user.Password) {
		http.Error(w, "Invalid email or password", http.StatusUnauthorized)
		return
	}
	// Generate JWT token
	token, err := middleware.GenerateToken(user.ID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	json.NewEncoder(w).Encode(map[string]string{"token": token})
}
```

## Step 4: Testing

```go
// File: integration_test.go

package main

import (
	"bytes"
	"database/sql"
	"encoding/json"
	"fmt"
	"net/http"
	"net/http/httptest"
	"os"
	"testing"

	"github.com/anoying-kid/go-apps/blogAPI/internal/handlers"
	"github.com/anoying-kid/go-apps/blogAPI/internal/middleware"
	"github.com/anoying-kid/go-apps/blogAPI/internal/repository"
	"github.com/gorilla/mux"
	_ "github.com/lib/pq"
	"github.com/stretchr/testify/assert"
)

var (
	router *mux.Router
	db     *sql.DB
)

type TestUser struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

type LoginResponse struct {
	Token string `json:"token"`
}

type Post struct {
	ID       int64  `json:"id"`
	Title    string `json:"title"`
	Body     string `json:"body"`
	AuthorID int64  `json:"author_id"`
}

func TestMain(m *testing.M) {
	// Setup
	var err error
	dsn := "host=localhost user=postgres password=mysecretpassword dbname=userdb_test port=5432 sslmode=disable"
	db, err = sql.Open("postgres", dsn)
	if err != nil {
		fmt.Printf("Failed to connect to test database: %v\n", err)
		os.Exit(1)
	}

	// Initialize repositories and handlers
	userRepo := repository.NewUserRepository(db)
	userHandler := handlers.NewUserHandler(userRepo)

	postRepo := repository.NewPostRepository(db)
	postHandler := handlers.NewPostHandler(postRepo)

	router = mux.NewRouter()
	router.HandleFunc("/api/register", userHandler.Register).Methods("POST")
	router.HandleFunc("/api/login", userHandler.Login).Methods("POST")
	router.HandleFunc("/api/posts", middleware.AuthMiddleware(postHandler.Create)).Methods("POST")
	router.HandleFunc("/api/posts/{id}", middleware.AuthMiddleware(postHandler.Update)).Methods("PUT")
	router.HandleFunc("/api/posts/{id}", postHandler.Get).Methods("GET")
	router.HandleFunc("/api/posts", postHandler.List).Methods("GET")

	// Run tests
	code := m.Run()

	// Cleanup
	cleanupDatabase()
	db.Close()

	os.Exit(code)
}

func cleanupDatabase() {
	db.Exec("DELETE FROM posts")
	db.Exec("DELETE FROM users")
}

func TestUserRegistrationAndLogin(t *testing.T) {
	cleanupDatabase()

	// Test user registration
	user := TestUser{
		Username: "testuser",
		Password: "testpass123",
	}

	// Register user
	t.Run("Register User", func(t *testing.T) {
		body, _ := json.Marshal(user)
		req := httptest.NewRequest("POST", "/api/register", bytes.NewBuffer(body))
		req.Header.Set("Content-Type", "application/json")

		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)

		assert.Equal(t, http.StatusCreated, rr.Code)
	})

	// Login user
	t.Run("Login User", func(t *testing.T) {
		body, _ := json.Marshal(user)
		req := httptest.NewRequest("POST", "/api/login", bytes.NewBuffer(body))
		req.Header.Set("Content-Type", "application/json")

		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)

		assert.Equal(t, http.StatusOK, rr.Code)

		var loginResp LoginResponse
		err := json.NewDecoder(rr.Body).Decode(&loginResp)
		assert.NoError(t, err)
		assert.NotEmpty(t, loginResp.Token)
	})
}

func TestPostOperations(t *testing.T) {
    cleanupDatabase()

    // First register and login to get token
    user := TestUser{
        Username: "postuser",
        Password: "postpass123",
    }

    // Register
    body, _ := json.Marshal(user)
    req := httptest.NewRequest("POST", "/api/register", bytes.NewBuffer(body))
    req.Header.Set("Content-Type", "application/json")
    rr := httptest.NewRecorder()
    router.ServeHTTP(rr, req)

    // Login to get token
    req = httptest.NewRequest("POST", "/api/login", bytes.NewBuffer(body))
    req.Header.Set("Content-Type", "application/json")
    rr = httptest.NewRecorder()
    router.ServeHTTP(rr, req)

    var loginResp LoginResponse
    json.NewDecoder(rr.Body).Decode(&loginResp)
    token := loginResp.Token

    // Test creating a post
    t.Run("Create Post", func(t *testing.T) {
        post := map[string]string{
            "title": "Test Post",
            "body":  "This is a test post body",
        }
        body, _ := json.Marshal(post)
        req := httptest.NewRequest("POST", "/api/posts", bytes.NewBuffer(body))
        req.Header.Set("Content-Type", "application/json")
        req.Header.Set("Authorization", "Bearer "+token)

        rr := httptest.NewRecorder()
        router.ServeHTTP(rr, req)

        assert.Equal(t, http.StatusCreated, rr.Code)

        var createdPost Post
        err := json.NewDecoder(rr.Body).Decode(&createdPost)
        assert.NoError(t, err)
        assert.Equal(t, post["title"], createdPost.Title)
        assert.Equal(t, post["body"], createdPost.Body)
    })

	t.Run("Update Post", func(t *testing.T) {
		// Create a post first to ensure we're the owner
		createPost := map[string]string{
			"title": "Initial Test Post",
			"body":  "This is the initial body",
		}
		createBody, _ := json.Marshal(createPost)
		createReq := httptest.NewRequest("POST", "/api/posts", bytes.NewBuffer(createBody))
		createReq.Header.Set("Content-Type", "application/json")
		createReq.Header.Set("Authorization", "Bearer "+token)
		
		createRr := httptest.NewRecorder()
		router.ServeHTTP(createRr, createReq)
		
		var createdPost Post
		json.NewDecoder(createRr.Body).Decode(&createdPost)
		postID := createdPost.ID
	
		// Now update the post we just created
		updatePost := map[string]string{
			"title": "Updated Test Post",
			"body":  "This is an updated test post body",
		}
		updateBody, _ := json.Marshal(updatePost)
	
		// Send update request
		req := httptest.NewRequest("PUT", fmt.Sprintf("/api/posts/%d", postID), bytes.NewBuffer(updateBody))
		req.Header.Set("Content-Type", "application/json")
		req.Header.Set("Authorization", "Bearer "+token)
		
		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)
	
		assert.Equal(t, http.StatusOK, rr.Code)
	
		var updatedPost Post
		err := json.NewDecoder(rr.Body).Decode(&updatedPost)
		assert.NoError(t, err)
		assert.Equal(t, postID, updatedPost.ID)
		assert.Equal(t, updatePost["title"], updatedPost.Title)
		assert.Equal(t, updatePost["body"], updatedPost.Body)
	})

    // Test listing posts
    t.Run("List Posts", func(t *testing.T) {
        req := httptest.NewRequest("GET", "/api/posts", nil)
        rr := httptest.NewRecorder()
        router.ServeHTTP(rr, req)

        assert.Equal(t, http.StatusOK, rr.Code)

        var posts []Post
        err := json.NewDecoder(rr.Body).Decode(&posts)
        assert.NoError(t, err)
        assert.NotEmpty(t, posts)
    })

    // Test getting a specific post
    t.Run("Get Post", func(t *testing.T) {
        // First, list posts to get an ID
        req := httptest.NewRequest("GET", "/api/posts", nil)
        rr := httptest.NewRecorder()
        router.ServeHTTP(rr, req)

        var posts []Post
        json.NewDecoder(rr.Body).Decode(&posts)
        postID := posts[0].ID

        // Now get the specific post
        req = httptest.NewRequest("GET", fmt.Sprintf("/api/posts/%d", postID), nil)
        rr = httptest.NewRecorder()
        router.ServeHTTP(rr, req)

        assert.Equal(t, http.StatusOK, rr.Code)

        var post Post
        err := json.NewDecoder(rr.Body).Decode(&post)
        assert.NoError(t, err)
        assert.Equal(t, postID, post.ID)
    })
    
}

func TestInvalidOperations(t *testing.T) {
	cleanupDatabase()

	// Test creating post without authentication
	t.Run("Create Post Without Auth", func(t *testing.T) {
		post := map[string]string{
			"title": "Test Post",
			"body":  "This is a test post body",
		}
		body, _ := json.Marshal(post)
		req := httptest.NewRequest("POST", "/api/posts", bytes.NewBuffer(body))
		req.Header.Set("Content-Type", "application/json")

		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)

		assert.Equal(t, http.StatusUnauthorized, rr.Code)
	})

	// Test invalid login
	t.Run("Invalid Login", func(t *testing.T) {
		user := TestUser{
			Username: "nonexistent",
			Password: "wrongpass",
		}
		body, _ := json.Marshal(user)
		req := httptest.NewRequest("POST", "/api/login", bytes.NewBuffer(body))
		req.Header.Set("Content-Type", "application/json")

		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)

		assert.Equal(t, http.StatusUnauthorized, rr.Code)
	})

	// Test getting non-existent post
	t.Run("Get Non-existent Post", func(t *testing.T) {
		req := httptest.NewRequest("GET", "/api/posts/99999", nil)
		rr := httptest.NewRecorder()
		router.ServeHTTP(rr, req)

		assert.Equal(t, http.StatusNotFound, rr.Code)
	})
}
```