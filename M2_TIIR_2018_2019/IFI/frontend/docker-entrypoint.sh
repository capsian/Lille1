#!/bin/baapish

echo "Entrypoint frontend"

#$BACKEND_URL=$(echo $BACKEND_URL)

if [ "$BACKEND_URL" = 'INJECT_URL' ]; then
	echo "BACKEND_URL not init !!!"
else
	echo "BACKEND_URL init with = $BACKEND_URL"
	echo "var url_api = $BACKEND_URL;" > /usr/share/nginx/html/js/var.js

fi

echo "Starting nginx ...."
exec nginx -g 'daemon off;'
