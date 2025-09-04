#!/bin/sh

cd /var/www/html

if [ ! -f ./wp-config.php ]; then

    wp core download    --allow-root --path=/var/www/html

    wp config create    --dbname="$MYSQL_DB_NAME" \
                        --dbuser="$MYSQL_ADMIN" \
                        --dbpass="$MYSQL_ADMIN_PASSWORD" \
                        --dbhost="$WORDPRESS_HOST" \
                        --allow-root

    wp core install     --url="macampos.42.fr" \
                        --title="Inception 42" \
                        --admin_user="$MYSQL_ADMIN" \
                        --admin_password="$MYSQL_ADMIN_PASSWORD" \
                        --admin_email="$MYSQL_ADMIN_EMAIL" \
                        --allow-root
    
    wp user create      $WORDPRESS_USER \
                        $WORDPRESS_USER_EMAIL \
                        --user_pass=$WORDPRESS_PASSWORD \
                        --role=author \
                        --allow-root
    
    wp theme activate   twentytwentyfour \
                        --allow-root 

fi

exec "$@"