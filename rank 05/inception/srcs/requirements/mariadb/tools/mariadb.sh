#!/bin/sh


if [ ! -d "/var/lib/mysql/$MYSQL_DB_NAME" ]; then

service mariadb start

mysql -u root <<EOF
SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$MYSQL_ROOT_PASSWORD');
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
FLUSH PRIVILEGES;
EOF

mysql -u root -p"$MYSQL_ROOT_PASSWORD" <<EOF
    CREATE DATABASE IF NOT EXISTS $MYSQL_DB_NAME;
    CREATE USER IF NOT EXISTS '$MYSQL_ADMIN'@'%' IDENTIFIED BY '$MYSQL_ADMIN_PASSWORD';
    GRANT ALL PRIVILEGES ON $MYSQL_DB_NAME.* TO '$MYSQL_ADMIN'@'%';
    FLUSH PRIVILEGES;
EOF

sleep 3

service mariadb stop

fi

exec "$@"