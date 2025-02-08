docker exec -t postgresql pg_dump -U postgres -d pthm_db -F c -f /var/lib/postgresql/data/db_backup.dump
docker cp postgresql:/var/lib/postgresql/data/db_backup.dump ./db_backup.dump