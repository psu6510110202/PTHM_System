docker cp data_backup.dump postgresql:/var/lib/postgresql/data/data_backup.dump
docker exec -t postgresql pg_restore -U postgres -d pthm_db --data-only /var/lib/postgresql/data/data_backup.dump
