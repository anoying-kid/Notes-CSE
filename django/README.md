# Django Notes

Creating a Django project

```bash
python3 -m venv venv #creating virtual environment
source venv/bin/activate #activating the environment
pip3 install django #installing django
django-admin startproject project_name .
```

To sync the database with default settings

```bash
python3 manage.py migrate
python3 manage.py runserver
```

# Project 1 : Library Website

* Setup the django Project
* Create a new app name "books"
```bash
python3 manage.py startapp books
```
* Add your app to the INSTALLED_APPS
```python
# django_project/settings.py
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    # Local
    "books.apps.BooksConfig",  # new
]
```

## Models
```python
# books/models.py
from django.db import models

class Book(models.Model):
    title = models.CharField(max_length=250) subtitle = models.CharField(max_length=250) author = models.CharField(max_length=100) isbn = models.CharField(max_length=13)

    def __str__(self):
        return self.title
```

Now add this changes to database

```bash
python3 manage.py makemigrations books
```

## Admin

Creating superuser account

```bash
python3 manage.py createsuperuser
```

Now registering the superuser

```python
# books/admin.py
from django.contrib import admin
from .models import Book
admin.site.register(Book)
```

Run the server

```bash
python3 manage.py runserver
```

You can check the admin panel at `http://127.0.0.1:8000/admin`.

Add some book by Clicking '+'.

## Views

The views.py file controls how the database model content is displayed.

```python
# books/views.py
from django.views.generic
import ListView from .models import Book

class BookListView(ListView):
    model = Book
    template_name = "book_list.html"
```

## URLs

Adding URLs to both project-level.

```python
# django_project/urls.py
from django.contrib import admin
from django.urls import path, include # new
urlpatterns = [
    path("admin/", admin.site.urls),
    path("", include("books.urls")),  # new
]
```

Now in books

```python
# books/urls.py
from django.urls import path
from .views import BookListView
urlpatterns = [
    path("", BookListView.as_view(), name="home"),
]
```

## Templates

The final step is to create our template file that controls the layout on the actual web page.

```bash
mkdir books/templates
mkdir books/templates/books
```

```django
<!-- books/templates/books/book_list.html -->
<h1>All books</h1>
{% for book in book_list %} <ul>
<li>Title: {{ book.title }}</li> <li>Subtitle: {{ book.subtitle }}</li> <li>Author: {{ book.author }}</li> <li>ISBN: {{ book.isbn }}</li>
</ul>
{% endfor %}
```

Runserver

```bash
py manage.py runserver
```

## Tests

Tests are a vital part of writing software and we should add them now before moving on to the API portion of this project.

```python
# books/tests.py
from django.test import TestCase
from django.urls import reverse
from .models import Book
class BookTests(TestCase):
    @classmethod
    def setUpTestData(cls):
        cls.book = Book.objects.create(
                    title="A good title",
                    subtitle="An excellent subtitle",
                    author="Tom Christie",
                    isbn="1234567890123",
        )
        
        def test_book_content(self):
            self.assertEqual(self.book.title, "A good title")
            self.assertEqual(self.book.subtitle, "An excellent subtitle")
            self.assertEqual(self.book.author, "Tom Christie")
            self.assertEqual(self.book.isbn, "1234567890123")
        
        def test_book_listview(self):
            response = self.client.get(reverse("home"))
            self.assertEqual(response.status_code, 200)
            self.assertContains(response, "excellent subtitle")
            self.assertTemplateUsed(response, "books/book_list.html")
```

Run Tests
```shell
py manage.py test
```

# Creating the Api

* Drf library suitable for creating api in django
```bash
pip install djangorestframework
```
* Add to `INSTALLED_APPS`

```python
# django_project/settings.py
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    # 3rd party
    "rest_framework",  # new
    # Local
    "books.apps.BooksConfig",
]
```

* Creating a new app apis
```bash
py manage.py startapp apis
```

* Add to `INSTALLED_APPS`
```python
# django_project/settings.py
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    # 3rd party
    "rest_framework",
    # Local
    "books.apps.BooksConfig",
    "apis.apps.ApisConfig",  # new
]
```

## URLs

Adding url to both the project-level

```python
# django_project/urls.py
from django.contrib import admin
from django.urls import path, include
urlpatterns = [
    path("admin/", admin.site.urls),
    path("api/", include("apis.urls")),  # new
    path("", include("books.urls")),
]
```

Now in apis

```python
# apis/urls.py
from django.urls import path
from .views import BookAPIView
urlpatterns = [
    path("", BookAPIView.as_view(), name="book_list"),
]
```

## Views

Django REST Framework views are similar except the end result is serialized data in JSON format, not the content for a web page!

```python
# apis/views.py
from rest_framework import generics from books.models import Book
from .serializers import BookSerializer
class BookAPIView(generics.ListAPIView): queryset = Book.objects.all() serializer_class = BookSerializer
```

## Serializers

A serializer33 translates complex data like querysets and model instances into a format that is easy to consume over the internet, typically JSON.
```python
# apis/serializers.py
from rest_framework import serializers from books.models import Book
class BookSerializer(serializers.ModelSerializer): class Meta:
        model = Book
        fields = ("title", "subtitle", "author", "isbn")
```

## Browsable API

Raw JSON data is not particularly friendly to consume with human eyes. Fortunately, Django REST Framework ships with a built-in browsable API that displays both the content and HTTP verbs associated with a given endpoint.

```shell
python manage.py runserver
```

## Tests

```python
# apis/tests.py
from django.urls import reverse
from rest_framework import status
from rest_framework.test import APITestCase
from books.models import Book

class APITests(APITestCase):
    @classmethod
    def setUpTestData(cls):
        cls.book = Book.objects.create(
                    title="Django for APIs",
                    subtitle="Build web APIs with Python and Django",
                    author="William S. Vincent",
                    isbn="9781735467221",
        )
        
    def test_api_listview(self):
        response = self.client.get(reverse("book_list"))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(Book.objects.count(), 1)
        self.assertContains(response, self.book)
```

For running all the test case.
```shell
python manage.py test
```

For running particular app test case.
```shell
python manage.py test apis
```

## Static Files

Creating static folder
```shell
mkdir static
```

Installing whitenoise
```shell
pip install whitenoise
```

Setup the whitenoise
```python
# django_project/settings.py
INSTALLED_APPS = [
    ...
    "whitenoise.runserver_nostatic",  # new
    "django.contrib.staticfiles",
]
MIDDLEWARE = [
    "django.middleware.security.SecurityMiddleware",
    "django.contrib.sessions.middleware.SessionMiddleware",
    "whitenoise.middleware.WhiteNoiseMiddleware",  # new
    ...
]
STATIC_URL = "/static/"
STATICFILES_DIRS = [BASE_DIR / "static"]  # new
STATIC_ROOT = BASE_DIR / "staticfiles"  # new
STATICFILES_STORAGE =
"whitenoise.storage.CompressedManifestStaticFilesStorage" # new
```

First time to compile all the static file directories and files into one self-contained unit suitable for deployment.
```shell
py manage.py collectstatic
```

