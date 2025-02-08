docker exec -t postgresql pg_dump -U postgres -d pthm_db --data-only -F c -f /var/lib/postgresql/data/data_backup.dump
docker cp postgresql:/var/lib/postgresql/data/data_backup.dump ./data_backup.dump