docker cp db_backup.dump postgresql:/var/lib/postgresql/data/db_backup.dump
docker exec -t postgresql pg_restore -U postgres -d pthm_db --clean --create /var/lib/postgresql/data/db_backup.dump
