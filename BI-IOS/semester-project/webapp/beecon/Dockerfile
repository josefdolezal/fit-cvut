FROM 3.4.4-onbuild

EXPOSE 8000

RUN python manage.py makemigrations \
    python manage.py migrate

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
