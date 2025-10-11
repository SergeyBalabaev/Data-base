FROM postgres:14

COPY migrate/create_db.sql migrate/insert_db.sql migrate/migrate.sh /migrate/
RUN chmod +x migrate/migrate.sh

ENTRYPOINT ["/migrate/migrate.sh"]